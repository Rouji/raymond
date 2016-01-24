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
class CSphereSceneObject : public CSceneObject
{
public:
    CSphereSceneObject(const vec3f& center = vec3f(0.0f), f32 radius = 1.0f) :
        m_Center(center), 
        m_Radius(radius)
    {}

    ~CSphereSceneObject(){}

    bool intersect(const ray3f& ray, SIntersection* pIntersect);

    void setPosition(const vec3f& p);
    const vec3f& getPosition();

    void setScale(const vec3f& p);
    const vec3f& getScale();

    void setRotation(const vec3f& p);
    const vec3f& getRotation();

    void setRadius(float r);
    float getRadius();

private:
    vec3f m_Center;
    f32 m_Radius;
};

} //scene
} //raymond

#endif // !__CSPHERE_H

