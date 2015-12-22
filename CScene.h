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

class CScene
{
public:
    CScene();
    ~CScene();

    void addSceneObject(CSceneObject* pObj);
    void addLight(CLight* pLight);

    void setCamera(CCamera* pCam);

    void setClearColour(const col4f& col);

    void setImagePath(const char* path);

    u32 render();

    //removes all objects and lights from scene
    void clear();

private:
    //recursive ray-trace function
    col4f trace(const ray3f& ray, u32 depth = 0);
    CSceneObject* intersectScene(const ray3f& ray, SIntersection* pIntersect);
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

