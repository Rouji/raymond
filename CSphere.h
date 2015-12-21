#ifndef __CSPHERE_H
#define __CSPHERE_H

#include "vec3.h"
#include "CSceneObject.h"

namespace raymond
{

class Sphere : protected CSceneObject
{
public:
    bool intersect(const ray3f& ray, SIntersection* pIntersect);

    Sphere& setPosition(const vec3f& p);
    const vec3f& getPosition();

    Sphere& setRadius(float r);
    float getRadius();

private:
    vec3f m_Center;
    float m_Radius;
};

} //raymond

#endif // !__CSPHERE_H

