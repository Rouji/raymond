#ifndef __CMESHSCENEOBJECT_H
#define __CMESHSCENEOBJECT_H

#include "vec3.h"
#include "ray3.h"
#include "CSceneObject.h"
#include "CMesh.h"
#include <vector>

namespace raymond
{
namespace scene
{

class CMeshSceneObject : public CSceneObject
{
public:
    CMeshSceneObject();
    ~CMeshSceneObject();

    bool intersect(const ray3f& ray, SIntersection* pIntersect);

    void setPosition(const vec3f& p);
    const vec3f& getPosition();

    void setScale(const vec3f& p);
    const vec3f& getScale();

    void setRotation(const vec3f& p);
    const vec3f& getRotation();

    void setMesh(CMesh* pMesh);

private:
    CMesh* m_pMesh;

    //TODO: this is kind of a hack
    std::vector<triangle3f> m_faces;
    std::vector<vec3f> m_normals;

    vec3f m_pos;
};


}
}
#endif // !__CMESHSCENEOBJECT_H

