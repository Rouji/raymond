#ifndef __CSCENE_H
#define __CSCENE_H

#include <list>

#include "CSceneObject.h"
#include "CCamera.h"
#include "CLight.h"

namespace raymond
{
namespace scene
{

//manages and renders a scene
//note: objects passed to the add*/set* functions via pointer
//      WILL be deleted by this class, so don't manage them outside of it
//TODO: implement reference counting or something to make this less ugly
class CScene
{
public:
    CScene();
    ~CScene();

    void addSceneObject(CSceneObject* pObj);
    void addLight(CLight* pLight);

    //set camera
    //TODO: support multiple cameras?
    void setCamera(CCamera* pCam);

    //set the colour for rays going off into nowhere
    void setClearColour(const col4f& col);

    //set output file path
    void setImagePath(const char* path);

    //renders everything
    u32 render();

    //removes all objects and lights from scene
    void clear();

private:
    //recursive ray-trace function
    //note: doesn't actually recurse yet, at all
    col4f trace(const ray3f& ray, u32 depth = 0);

    //find nearest intersection among all sceneobjects
    CSceneObject* intersectScene(const ray3f& ray, SIntersection* pIntersect);

    //find out if a light source is blocked from a certain point
    bool intersectShadow(const vec3f& origin, CLight* pLight);

    std::list<CSceneObject*> m_objectList;
    std::list<CLight*> m_lightList;
    CCamera* m_pCamera;
    col4f m_clearCol;
    char m_imagePath[512];
};

} //scene
} //raymond

#endif // !__CSCENE_H

