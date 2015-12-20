#ifndef __SCENEOBJECT_H
#define __SCENEOBJECT_H

#include "vec3.h"
#include "ray3.h"

namespace raymond
{

class SceneObject
{
public:
    SceneObject() {};
    ~SceneObject() {};

    virtual bool intersect(const ray3f& ray, float* pIntersect) = 0;
};

} //raymond

#endif // !__SCENEOBJECT_H

