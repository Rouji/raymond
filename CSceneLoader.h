#ifndef __CSCENELOADER_H
#define __CSCENELOADER_H

#include "CScene.h"
#include "CSphere.h"
#include "tinyxml2/tinyxml2.h"

namespace raymond
{
namespace scene
{

//reads XML, creates a CScene object
class CSceneLoader
{
public:
    CSceneLoader();
    ~CSceneLoader();

    //note: the returned object has to be deleted after use
    CScene* loadXML(const char* path);
private:
    CCamera* xmlElemToCamera(tinyxml2::XMLElement* pElem);
    CLight* xmlElemToLight(tinyxml2::XMLElement* pElem);
    CSphereSceneObject* xmlElemToSphere(tinyxml2::XMLElement* pElem);
    CSceneObject* xmlElemToSceneObject(tinyxml2::XMLElement* pElem);
    u32 xmlElemToMaterial(tinyxml2::XMLElement* pElem, SMaterial* pMat);

    vec3f xmlElemToVec(tinyxml2::XMLElement* pElem);
    col4f xmlElemToColour(tinyxml2::XMLElement* pElem);
    f32 xmlElemGetFloatAttrib(tinyxml2::XMLElement* pElem, const char* attrName);
    s32 xmlElemGetIntAttrib(tinyxml2::XMLElement* pElem, const char* attrName);
};

} //scene
} //raymond

#endif // !__CSCENELOADER_H

