#ifndef __CSPHERE_H
#define __CSPHERE_H

#include "vec3.h"
#include "CSceneObject.h"

namespace raymond
{
namespace scene
{

class CSphere : public CSceneObject
{
public:
    bool intersect(const ray3f& ray, SIntersection* pIntersect);

    CSphere& setPosition(const vec3f& p);
    const vec3f& getPosition();

    CSphere& setRadius(float r);
    float getRadius();

private:
    vec3f m_Center;
    f32 m_Radius;
};

} //scene
} //raymond

#endif // !__CSPHERE_H

