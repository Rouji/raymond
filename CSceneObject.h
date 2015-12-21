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

//abstract class for scene objects
class CSceneObject
{
public:
    SMaterial Material;

    CSceneObject() {};
    virtual ~CSceneObject() {};

    //has to be implemented by all inherited classes
    virtual bool intersect(const ray3f& ray, SIntersection* pIntersect) = 0;
};

} //scene
} //raymond

#endif // !__CSCENEOBJECT_H

