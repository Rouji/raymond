#ifndef __CSCENEOBJECT_H
#define __CSCENEOBJECT_H

#include "vec3.h"
#include "ray3.h"
#include "SMaterial.h"

namespace raymond
{
namespace scene
{

struct SIntersection
{
    float Inter;
    vec3f Normal;
};

class CSceneObject
{
public:
    CSceneObject() {};
    ~CSceneObject() {};

    virtual bool intersect(const ray3f& ray, SIntersection* pIntersect) = 0;

    void setMaterial(const SMaterial& m)
    {
        m_material = m;
    }

    const SMaterial& getMaterial()
    {
        return m_material;
    }

protected:
    SMaterial m_material;
};

} //scene
} //raymond

#endif // !__CSCENEOBJECT_H

