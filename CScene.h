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

    void setImagePath(const s8* path);

    u32 render();

    //removes all objects and lights from scene
    void clear();

private:
    std::list<CSceneObject*> m_objectList;
    std::list<CLight*> m_lightList;
    CCamera* m_pCamera;
    col4f m_clearCol;
    const s8* m_imagePath;
};

} //scene
} //raymond

#endif // !__CSCENE_H

