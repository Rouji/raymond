#ifndef __CSCENELOADER_H
#define __CSCENELOADER_H

#include "CScene.h"
#include "tinyxml2/tinyxml2.h"

namespace raymond
{
namespace scene
{

class CSceneLoader
{
public:
    CSceneLoader();
    ~CSceneLoader();

    CScene* loadXML(const char* path);
private:
    CCamera* xmlElemToCamera(tinyxml2::XMLElement* pElem);
    CLight* xmlElemToLight(tinyxml2::XMLElement* pElem);

    vec3f xmlElemToVec(tinyxml2::XMLElement* pElem);
    col4f xmlElemToColour(tinyxml2::XMLElement* pElem);
    f32 xmlElemGetFloatAttrib(tinyxml2::XMLElement* pElem, const char* attrName);
    s32 xmlElemGetIntAttrib(tinyxml2::XMLElement* pElem, const char* attrName);
};

} //scene
} //raymond

#endif // !__CSCENELOADER_H

