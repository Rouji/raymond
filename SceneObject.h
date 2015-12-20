#ifndef __SCENEOBJECT_H
#define __SCENEOBJECT_H

#include "vec3.h"

namespace raymond
{

class SceneObject
{
public:
    SceneObject() {};
    ~SceneObject() {};

    virtual bool intersect(const vec3f& ray_orig, const vec3f& ray_dir, float* pIntersect) = 0;
};

} //raymond

#endif // !__SCENEOBJECT_H

