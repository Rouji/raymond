#include "CSceneLoader.h"

using namespace tinyxml2;

namespace raymond
{
namespace scene
{

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
        //TODO: "error loading file"
        return 0;
    }

    XMLElement* pChild = 0; //used as general child pointer
    XMLElement* pLightsElement = 0;
    XMLElement* pObjectsElement = 0;
    XMLElement* pSceneElement = doc.FirstChildElement("scene");
    if (!pSceneElement)
    {
        //TODO: "no scene element"
        return 0;
    }
    if (!pSceneElement->FirstChild())
    {
        //TODO: "scene element empty"
        return 0;
    }

    const s8* output_file = (const s8*)pSceneElement->Attribute("output_file");
    if (!output_file)
    {
        //TODO: "no output file specified"
        return 0;
    }

    CScene* pNewScene = new CScene();

    //load background colour
    if (pChild = pSceneElement->FirstChildElement("background_color"))
    {
        pNewScene->setClearColour(xmlElemToColour(pChild));
    }

    //load camera
    if (pChild = pSceneElement->FirstChildElement("camera"))
    {
        pNewScene->setCamera(xmlElemToCamera(pChild));
    }
    else
    {
        //TODO: "no camera defined"
    }

    //load lights
    pLightsElement = pSceneElement->FirstChildElement("lights");
    CLight* pLightTmp = 0;
    if (pLightsElement)
    {
        for (pChild = pLightsElement->FirstChildElement(); pChild; pChild = pChild->NextSiblingElement())
        {
            const char* tmp = pChild->Name();
            pLightTmp = xmlElemToLight(pChild);
            if (pLightTmp)
                pNewScene->addLight(pLightTmp);
        }
    }


    //load objects
    pObjectsElement = pSceneElement->FirstChildElement("surfaces");
    CSceneObject* pObjTmp = 0;
    if (pObjectsElement)
    {
        //TODO
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
        //TODO: "missing essential positional data"
        return 0;
    }
    if (!pFOVElem ||
        !pResElem ||
        !pBouncesElem)
    {
        //TODO: "notice: some data missing, using defaults"
    }

    CCamera* pNewCam = new CCamera(xmlElemToVec(pPosElem),
                                   xmlElemToVec(pLookAtElem),
                                   xmlElemToVec(pUpElem));
    if (pFOVElem) pNewCam->setFOV(xmlElemGetFloatAttrib(pFOVElem, "angle"));
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
        //TODO: "light has no colour specified"
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

vec3f CSceneLoader::xmlElemToVec(tinyxml2::XMLElement* pElem)
{
    //TODO: error checks
    vec3f vec;
    pElem->QueryFloatAttribute("x", &vec.X);
    pElem->QueryFloatAttribute("y", &vec.Y);
    pElem->QueryFloatAttribute("z", &vec.Z);
    return vec;
}

col4f CSceneLoader::xmlElemToColour(tinyxml2::XMLElement* pElem)
{
    //TODO: error checks
    col4f col;
    pElem->QueryFloatAttribute("r", &col.R);
    pElem->QueryFloatAttribute("g", &col.G);
    pElem->QueryFloatAttribute("b", &col.B);
    pElem->QueryFloatAttribute("a", &col.A);
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