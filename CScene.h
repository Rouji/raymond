#ifndef __CSCENE_H
#define __CSCENE_H

#include <list>

#include "CSceneObject.h"
#include "CCamera.h"

namespace raymond
{
class CScene
{
public:
    CScene();
    ~CScene();

    void addSceneObject(CSceneObject* pObj);


private:
    std::list<CSceneObject*> m_objectList;
    CCamera m_camera;

};

} //raymond

#endif // !__CSCENE_H

