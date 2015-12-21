#include "CScene.h"
#include "CPPMImageWriter.h"

namespace raymond
{
namespace scene
{

CScene::CScene() :
    m_clearCol(0.0f),
    m_pCamera(0)
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
    sprintf(m_imagePath, "%s.ppm", path);
    //memcpy(m_imagePath, path, strlen(path)+1);
}

u32 CScene::render()
{
    dim2i imageSize = m_pCamera->getImageSize();
    io::CPPMImageWriter writer(imageSize);
    ray3f ray;
    col4f pixelCol;
    for (s32 y = 0; y < imageSize.Y; ++y)
    {
        for (s32 x = 0; x < imageSize.X; ++x)
        {
            ray = m_pCamera->getRay(vec2i(x, y));
            pixelCol = trace(ray);
            writer.SetPixel(dim2i(x, y), pixelCol);
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
    CSceneObject* pCurrObj = 0;
    col4f overallCol(0.0f);
    SIntersection intersect;
    f32 nearestSquared = 0;
    f32 distSquared = 0;

    //iterate throug all scene objects
    //find nearest intersection to ray origin
    for (std::list<CSceneObject*>::iterator it = m_objectList.begin();
         it != m_objectList.end();
         it++)
    {
        if ((*it)->intersect(ray, &intersect))
        {
            distSquared = ray.getOrigin().distanceSquared(intersect.IntersectionPoint);
            if (!pCurrObj || distSquared < nearestSquared)
            {
                pCurrObj = *it;
                nearestSquared = distSquared;
            }
        }
    }

    //no intersection found, return clear colour
    if (!pCurrObj)
    {
        return m_clearCol;
    }
    
    //debug
    //return col4f((intersect.Normal + 1.0f) / 2.0f);
    return pCurrObj->Material.Colour;

    /*
    //iterate through light sources
    for (std::list<CSceneObject*>::iterator it = m_objectList.begin();
    it != m_objectList.end();
        it++)
    {
        //TODO
    }*/
    

    return m_clearCol;
}

}//scene
}//raymond