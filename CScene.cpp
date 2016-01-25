#include "CScene.h"
#include "CPPMImageWriter.h"
#include "Log.h"
#include <stdio.h>

namespace raymond
{
namespace scene
{

//distance to add between a surface and ray cast from it
const f32 RECAST_MARGIN = FLOAT_ROUNDING_ERROR_32 * 10.0f; 

CScene::CScene() :
    m_pCamera(0),
    m_clearCol(0.0f)
{}

CScene::~CScene()
{
    clear();
}

void CScene::addSceneObject(CSceneObject * pObj)
{
    m_objectList.push_back(pObj);
}

void CScene::addLight(CLight * pLight)
{
    m_lightList.push_back(pLight);
}

void CScene::setCamera(CCamera * pCam)
{
    //delete old camera object
    if (m_pCamera)
        delete m_pCamera;

    m_pCamera = pCam;
}

void CScene::setClearColour(const col4f& col)
{
    m_clearCol = col;
}

void CScene::setImagePath(const char* path)
{
    //TODO: prevent buffer overruns etc. (oh noez my security)
    sprintf(m_imagePath, "%s.ppm", path);
}

u32 CScene::render()
{
    dim2i imageSize = m_pCamera->getImageSize();
    io::CPPMImageWriter writer(imageSize);
    ray3f ray;
    col4f pixelCol;
    for (u32 y = 0; y < imageSize.Y; ++y)
    {
        for (u32 x = 0; x < imageSize.X; ++x)
        {
            ray = m_pCamera->getRay(vec2i((s32)x, (s32)y));
            pixelCol = trace(ray,m_pCamera->getMaxBounces());
            writer.SetPixel(dim2i((s32)x, (s32)y), pixelCol);
        }
    }
    writer.Write(m_imagePath);
    return 0;
}

void CScene::clear()
{
    //clear objects
    for (std::list<CSceneObject*>::iterator it = m_objectList.begin();
         it != m_objectList.end();
         it++)
    {
        delete *it;
    }
    m_objectList.clear();

    //clear lights
    for (std::list<CLight*>::iterator it = m_lightList.begin();
         it != m_lightList.end();
         it++)
    {
        delete *it;
    }
    m_lightList.clear();

    //delete camera
    if (m_pCamera)
        delete m_pCamera;
}

col4f CScene::trace(const ray3f& ray, u32 depth)
{
    --depth;
    col4f overallCol(0.0f);
    SIntersection intersect;
    vec3f interAddMargin;
    CSceneObject* pCurrObj = intersectScene(ray, &intersect);

    //no intersection found, return clear colour
    if (!pCurrObj)
    {
        return m_clearCol;
    }
    
    //debug
    //return col4f((intersect.Normal + 1.0f) / 2.0f); //render normals
    //return pCurrObj->Material.Colour; //render base colour only
    //return col4f(1.0f - (ray.getOrigin().distance(intersect.IntersectionPoint) / 10.0f),0.0f,0.0f); //render depth

    
    //---shadow rays
    //iterate through light sources
    interAddMargin = intersect.IntersectionPoint + (intersect.Normal * RECAST_MARGIN);//account for rounding errors
    for (std::list<CLight*>::iterator it = m_lightList.begin();
         it != m_lightList.end();
         it++)
    {
        if (!intersectShadow(interAddMargin, *it))
        {
            overallCol += (*it)->shade(intersect.IntersectionPoint,
                                       intersect.Normal,
                                       m_pCamera->getEyePoint(),
                                       pCurrObj->Material);
        }
    }

    //reached max. recursion depth 
    if (depth == 0)
        return overallCol;
    
    //lower to accommodate for reflectance etc.
    overallCol *= 1.0f - pCurrObj->Material.Reflectance - pCurrObj->Material.Transmittance;

    //---reflection
    if (pCurrObj->Material.Reflectance > 0.0f)
    {
        vec3f reflDir = -(ray.getDirection().mirrorAlongNormal(intersect.Normal));
        overallCol += trace(ray3f(intersect.IntersectionPoint, reflDir),depth) * pCurrObj->Material.Reflectance;
    }

    //---refraction
    if (pCurrObj->Material.Transmittance > 0.0f && pCurrObj->Material.Refraction > 0.0f)
    {
        f32 n; //IOR ratio
        f32 cosT;
        vec3f outDir;
        vec3f norm = intersect.Normal;
        const vec3f& rayDir = ray.getDirection();
        f32 cos = rayDir.dot(norm);

        if (cos < 0) //air->obj
        {
            n = 1.0f/pCurrObj->Material.Refraction;
            cos = -cos;
        }
        else //obj->air
        {
            n = pCurrObj->Material.Refraction;
            
            norm *= -1.0f;
        }

        cosT = 1.0f - maths::square(n) * (1.0f - maths::square(cos));
        

        //total internal refl.
        if (cosT < 0.0f)
        {
            vec3f reflDir = -(ray.getDirection().mirrorAlongNormal(norm));
            overallCol += trace(ray3f(intersect.IntersectionPoint, reflDir), depth) * pCurrObj->Material.Reflectance;
        }
        else
        {
            cosT = maths::squareroot(cosT);
            outDir = rayDir * n + (norm * ((n * cos) - cosT));

            interAddMargin = intersect.IntersectionPoint - (norm * RECAST_MARGIN);
            overallCol += trace(ray3f(interAddMargin, outDir), depth) * pCurrObj->Material.Transmittance;
        }
    }
    
    return overallCol;
}

//TODO: make pIntersect optional
CSceneObject* CScene::intersectScene(const ray3f & ray, SIntersection* pIntersect)
{
    CSceneObject* pNearestObj = 0;
    SIntersection tmpIntersect;
    f32 nearestSquared = 0;
    f32 distSquared = 0;

    //iterate throug all scene objects
    //find nearest intersection to ray origin
    for (std::list<CSceneObject*>::iterator it = m_objectList.begin();
         it != m_objectList.end();
         it++)
    {
        if ((*it)->intersect(ray, &tmpIntersect))
        {
            distSquared = ray.getOrigin().distanceSquared(tmpIntersect.IntersectionPoint);
            if (!pNearestObj || distSquared < nearestSquared)
            {
                pNearestObj = *it;
                nearestSquared = distSquared;
                *pIntersect = tmpIntersect;
            }
        }
    }

    return pNearestObj;
}

bool CScene::intersectShadow(const vec3f& origin, CLight* pLight)
{
    ray3f ray(origin);
    SIntersection inter;
    CSceneObject* pObj = 0;
    
    if (pLight->Type == CLight::LIGHT_AMBIENT)
        return false; //no use checking a ray against ambient
    else if (pLight->Type == CLight::LIGHT_PARALLEL)
    {
        ray.setDirection(-pLight->Direction);
        return intersectScene(ray, &inter) != 0;
    }
    else if (pLight->Type == CLight::LIGHT_POINT)
    {
        vec3f dir = pLight->Position - origin;
        ray.setDirection(dir);
        pObj = intersectScene(ray, &inter);
        return pObj != 0 && dir.lengthSquared() > origin.distanceSquared(inter.IntersectionPoint);
    }
    else if (pLight->Type == CLight::LIGHT_SPOT)
        return false;

    return false;
}

}//scene
}//raymond
