#ifndef __CSPHERE_H
#define __CSPHERE_H

#include "vec3.h"
#include "CSceneObject.h"

namespace raymond
{
namespace scene
{

//implements CSceneObject for spheres
//TODO: transformations
class CSphere : public CSceneObject
{
public:
    CSphere(const vec3f& center = vec3f(0.0f), f32 radius = 1.0f) :
        m_Center(center), 
        m_Radius(radius)
    {}

    ~CSphere(){}

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

