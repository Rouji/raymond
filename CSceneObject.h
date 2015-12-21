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
    vec3f IntersectionPoint;
    vec3f Normal;
};

class CSceneObject
{
public:
    SMaterial Material;

    CSceneObject() {};
    virtual ~CSceneObject() = 0;

    virtual bool intersect(const ray3f& ray, SIntersection* pIntersect) = 0;
};

} //scene
} //raymond

#endif // !__CSCENEOBJECT_H

