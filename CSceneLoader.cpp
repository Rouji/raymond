#include "CSceneLoader.h"
#include "Log.h"
#include "CMesh.h"
#include "CObjMesh.h"



namespace raymond
{
namespace scene
{

using namespace tinyxml2;
using namespace io;

CSceneLoader::CSceneLoader()
{
}

CSceneLoader::~CSceneLoader()
{
}

CScene* CSceneLoader::loadXML(const char* path)
{
    if (!path)
        return 0;

    XMLDocument doc;
    if (doc.LoadFile((const char*)path) != tinyxml2::XML_NO_ERROR)
    {
        LogError("[SceneLoader] Couldn't find file \"%s\"\n",path);
        return 0;
    }

    XMLElement* pChild = 0; //used as general child pointer
    XMLElement* pLightsElement = 0;
    XMLElement* pObjectsElement = 0;
    XMLElement* pSceneElement = doc.FirstChildElement("scene");
    if (!pSceneElement)
    {
        LogError("[SceneLoader] Root \"scene\" node not found\n");
        return 0;
    }
    if (!pSceneElement->FirstChild())
    {
        LogError("[SceneLoader] \"scene\" node is empty\n");
        return 0;
    }

    const char* output_file = pSceneElement->Attribute("output_file");
    if (!output_file)
    {
        LogError("[SceneLoader] No output file specified\n");
        return 0;
    }

    CScene* pNewScene = new CScene();

    pNewScene->setImagePath(output_file);

    //load background colour
    if (pChild = pSceneElement->FirstChildElement("background_color"))
    {
        pNewScene->setClearColour(xmlElemToColour(pChild));
    }

    //load camera
    if (pChild = pSceneElement->FirstChildElement("camera"))
    {
        CCamera* pCam = xmlElemToCamera(pChild);
        if (!pCam)
        {
            LogError("[SceneLoader] Failed loading camera node\n");
            return 0;
        }
        pNewScene->setCamera(pCam);
    }
    else
    {
        LogError("[SceneLoader] No camera specified in scene\n");
    }

    //load lights
    pLightsElement = pSceneElement->FirstChildElement("lights");
    CLight* pLightTmp = 0;
    if (pLightsElement)
    {
        for (pChild = pLightsElement->FirstChildElement(); pChild; pChild = pChild->NextSiblingElement())
        {
            pLightTmp = xmlElemToLight(pChild);
            if (pLightTmp)
                pNewScene->addLight(pLightTmp);
        }
    }
    if (!pLightTmp)
    {
        LogError("[SceneLoader] No lights specified in scene\n");
        return 0;
    }


    //load objects
    pObjectsElement = pSceneElement->FirstChildElement("surfaces");
    CSceneObject* pObjTmp = 0;
    if (pObjectsElement)
    {
        for (pChild = pObjectsElement->FirstChildElement(); pChild; pChild = pChild->NextSiblingElement())
        {
            pObjTmp = xmlElemToSceneObject(pChild);
            if (pObjTmp)
                pNewScene->addSceneObject(pObjTmp);
        }
    }
    else
    {
        LogError("[SceneLoader] No renderable surfaces found\n");
    }

    return pNewScene;
}

CCamera* CSceneLoader::xmlElemToCamera(tinyxml2::XMLElement* pElem)
{
    XMLElement* pPosElem     = pElem->FirstChildElement("position");
    XMLElement* pLookAtElem  = pElem->FirstChildElement("lookat");
    XMLElement* pUpElem      = pElem->FirstChildElement("up");
    XMLElement* pFOVElem     = pElem->FirstChildElement("horizontal_fov");
    XMLElement* pResElem     = pElem->FirstChildElement("resolution");
    XMLElement* pBouncesElem = pElem->FirstChildElement("max_bounces");
    if (!pPosElem    ||
        !pLookAtElem ||
        !pUpElem)
    {
        LogError("[SceneLoader] Camera element is missing positional data\n");
        return 0;
    }
    if (!pFOVElem ||
        !pResElem ||
        !pBouncesElem)
    {
        LogError("[SceneLoader] Some camera parameters missing, using defaults\n");
    }

    CCamera* pNewCam = new CCamera(xmlElemToVec(pPosElem),
                                   xmlElemToVec(pLookAtElem),
                                   xmlElemToVec(pUpElem));
    if (pFOVElem) pNewCam->setFOV(2*DEG_TO_RAD * xmlElemGetFloatAttrib(pFOVElem, "angle"));
    if (pLookAtElem) pNewCam->setLookAtPoint(xmlElemToVec(pLookAtElem));
    if (pResElem) pNewCam->setImageSize(dim2i(xmlElemGetIntAttrib(pResElem, "horizontal"), xmlElemGetIntAttrib(pResElem, "vertical")));
    if (pBouncesElem) pNewCam->setMaxBounces(xmlElemGetIntAttrib(pBouncesElem, "n"));
    
    return pNewCam;
}

CLight * CSceneLoader::xmlElemToLight(tinyxml2::XMLElement * pElem)
{
    CLight::LightType type = CLight::LIGHT_AMBIENT; //default to ambient
    XMLElement* pColElem   = pElem->FirstChildElement("color");
    XMLElement* pDirElem   = pElem->FirstChildElement("direction");
    XMLElement* pPosElem   = pElem->FirstChildElement("position");
    XMLElement* pFallElem  = pElem->FirstChildElement("falloff");
    if (!pColElem)
    {
        LogError("[SceneLoader] No colour specified in light node\n");
        return 0;
    }

    if (XMLUtil::StringEqual(pElem->Name(), "parallel_light"))
        type = CLight::LIGHT_PARALLEL;
    else if (XMLUtil::StringEqual(pElem->Name(), "point_light"))
        type = CLight::LIGHT_POINT;
    else if (XMLUtil::StringEqual(pElem->Name(), "spot_light"))
        type = CLight::LIGHT_SPOT;

    CLight* pNewLight = new CLight();
    pNewLight->Type = type;
    pNewLight->Colour = xmlElemToColour(pColElem);
    if (pDirElem) pNewLight->Direction = xmlElemToVec(pDirElem);
    if (pPosElem) pNewLight->Position  = xmlElemToVec(pPosElem);
    if (pFallElem)
    {
        pNewLight->FalloffAlpha1 = xmlElemGetFloatAttrib(pFallElem, "alpha1");
        pNewLight->FalloffAlpha2 = xmlElemGetFloatAttrib(pFallElem, "alpha2");
    }
    

    return pNewLight;
}


CSphereSceneObject* CSceneLoader::xmlElemToSphereObject(tinyxml2::XMLElement* pElem)
{
    XMLElement* pPosElem = pElem->FirstChildElement("position");
    XMLElement* pMatElem = pElem->FirstChildElement("material_solid");
    if (!pMatElem) pMatElem = pElem->FirstChildElement("material_textured"); //try textured material as well

    if (!pPosElem ||
        !pMatElem)
    {
        LogError("[SceneLoader] Sphere element missing position or material\n");
        return 0;
    }

    float radius = xmlElemGetFloatAttrib(pElem, "radius");

    CSphereSceneObject* pNewSphere = new CSphereSceneObject();
    pNewSphere->setPosition(xmlElemToVec(pPosElem));
    pNewSphere->setRadius(radius);

    if (xmlElemToMaterial(pMatElem, &pNewSphere->Material))
    {
        LogError("[SceneLoader] Failed loading material for sphere\n");
        delete pNewSphere;
        return 0;
    }

    return pNewSphere;
}

CMeshSceneObject * CSceneLoader::xmlElemToMeshObject(tinyxml2::XMLElement * pElem)
{
    const char* name = pElem->Attribute("name");
    XMLElement* pMatElem = pElem->FirstChildElement("material_solid");
    if (!pMatElem) pMatElem = pElem->FirstChildElement("material_textured"); //try textured material as well

    if (!name)
    {
        LogError("[SceneLoader] Mesh element is missing a name (file path)\n");
        return 0;
    }
    if (!pMatElem)
    {
        LogError("[SceneLoader] Mesh element missing a material\n");
        return 0;
    }

    CObjMesh* pMesh = new CObjMesh();
    if (pMesh->load(name))
    {
        LogError("[SceneLoader] Failed loading mesh from '%s'\n", name);
        delete pMesh;
        return 0;
    }

    CMeshSceneObject* pNewMeshObj = new CMeshSceneObject();
    //TODO: mesh cache
    pNewMeshObj->setMesh(pMesh);

    if (xmlElemToMaterial(pMatElem, &pNewMeshObj->Material))
    {
        LogError("[SceneLoader] Failed loading material for sphere\n");
        delete pNewMeshObj;
        return 0;
    }

    return pNewMeshObj;
}

CSceneObject * CSceneLoader::xmlElemToSceneObject(tinyxml2::XMLElement * pElem)
{
    if (XMLUtil::StringEqual(pElem->Name(), "sphere"))
    {
        return xmlElemToSphereObject(pElem);
    }
    else if (XMLUtil::StringEqual(pElem->Name(), "mesh"))
    {
        return xmlElemToMeshObject(pElem);
    }
    else
    {
        LogError("[SceneLoader] Object type '%s' not supported\n", pElem->Name());
        return 0;
    }

    if (pElem->FirstChildElement("transform"))
    {
        LogError("[SceneLoader] Transformations not supported\n");
    }

    return 0;
}

u32 CSceneLoader::xmlElemToMaterial(tinyxml2::XMLElement* pElem, SMaterial* pMat)
{
    if (XMLUtil::StringEqual(pElem->Name(), "material_textured"))
    {
        Log("[SceneLoader] Textured materials not yet supported\n");
        return 0;
    }

    XMLElement* pColElem = pElem->FirstChildElement("color");
    XMLElement* pPhongElem = pElem->FirstChildElement("phong");
    XMLElement* pReflElem = pElem->FirstChildElement("reflectance");
    XMLElement* pTransElem = pElem->FirstChildElement("transmittance");
    XMLElement* pRefrElem = pElem->FirstChildElement("refraction");
    if (!pColElem   ||
        !pPhongElem ||
        !pReflElem  ||
        !pTransElem ||
        !pRefrElem)
    { 
        LogError("[SceneLoader] Material has missing parameters\n");
        return 1;
    }

    pMat->Colour = xmlElemToColour(pColElem);
    pMat->Reflectance   = xmlElemGetFloatAttrib(pReflElem,  "r");
    pMat->Refraction    = xmlElemGetFloatAttrib(pRefrElem,  "iof");
    pMat->Transmittance = xmlElemGetFloatAttrib(pTransElem, "t");
    pMat->ka  = xmlElemGetFloatAttrib(pPhongElem, "ka");
    pMat->kd  = xmlElemGetFloatAttrib(pPhongElem, "kd");
    pMat->ks  = xmlElemGetFloatAttrib(pPhongElem, "ks");
    pMat->exp = xmlElemGetFloatAttrib(pPhongElem, "exponent");
    
    return 0;
}

vec3f CSceneLoader::xmlElemToVec(tinyxml2::XMLElement* pElem)
{
    vec3f vec;
    if (pElem->QueryFloatAttribute("x", &vec.X) ||
        pElem->QueryFloatAttribute("y", &vec.Y) ||
        pElem->QueryFloatAttribute("z", &vec.Z))
    {
        LogError("[SceneLoader] Vector missing component(s)\n");
    }

    return vec;
}

col4f CSceneLoader::xmlElemToColour(tinyxml2::XMLElement* pElem)
{
    //TODO: error checks
    col4f col;
    pElem->QueryFloatAttribute("a", &col.A);
    if (pElem->QueryFloatAttribute("r", &col.R) ||
        pElem->QueryFloatAttribute("g", &col.G) ||
        pElem->QueryFloatAttribute("b", &col.B))
    {
        LogError("[SceneLoader] Colour missing component(s)\n");
    }
    return col;
}

f32 CSceneLoader::xmlElemGetFloatAttrib(tinyxml2::XMLElement* pElem, const char* attrName)
{
    f32 val = 0.0f;
    pElem->QueryFloatAttribute(attrName,&val);
    return val;
}

s32 CSceneLoader::xmlElemGetIntAttrib(tinyxml2::XMLElement * pElem, const char * attrName)
{
    s32 val = 0;
    pElem->QueryIntAttribute(attrName, &val);
    return val;
}

}//scene
}//raymond