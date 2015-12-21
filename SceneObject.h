#ifndef __SCENEOBJECT_H
#define __SCENEOBJECT_H

#include "vec3.h"
#include "ray3.h"
#include "Material.h"

namespace raymond
{

class Intersection
{
public:
    float Inter;
    vec3f Normal;
};

class SceneObject
{
public:
    SceneObject() {};
    ~SceneObject() {};

    virtual bool intersect(const ray3f& ray, Intersection* pIntersect) = 0;

    void setMaterial(const Material& m)
    {
        m_material = m;
    }

    const Material& getMaterial()
    {
        return m_material;
    }

protected:
    Material m_material;
};

} //raymond

#endif // !__SCENEOBJECT_H

