#ifndef __SPHERE_H
#define __SPHERE_H

#include "vec3.h"
#include "SceneObject.h"

namespace raymond
{

class Sphere : public SceneObject
{
public:
    bool intersect(const ray3f& ray, float* pIntersect);

    Sphere& setPosition(const vec3f& p);
    const vec3f& getPosition();

    Sphere& setRadius(float r);
    float getRadius();

private:
    vec3f m_Center;
    float m_Radius;
};

} //raymond

#endif // !__SPHERE_H

