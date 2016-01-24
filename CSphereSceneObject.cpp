#include "CSphereSceneObject.h"

namespace raymond
{
namespace scene
{

//ray-sphere intersection test based on a geometric approach
//TODO: implement a quadratic equation -variant instead?
bool CSphereSceneObject::intersect(const ray3f& ray, SIntersection* pIntersect)
{
    float int0, int1;
    float radiusSquared = maths::square(m_Radius);

    vec3f origToCenter = m_Center - ray.getOrigin();

    float distOrigDotCenter = origToCenter.dot(ray.getDirection());
    if (distOrigDotCenter < 0.0f)
        return false;

    float distSquared = origToCenter.dot(origToCenter) - maths::square(distOrigDotCenter);
    if (distSquared > radiusSquared) 
        return false;

    float distIntDotCenter = maths::squareroot(radiusSquared - distSquared);
    int0 = distOrigDotCenter - distIntDotCenter;
    int1 = distOrigDotCenter + distIntDotCenter;

    //pick the nearest, non-negative
    float intersectionDist = (int0 < int1 && int0 > 0.0f) ? int0 : int1; 
    if (intersectionDist < 0.0f) //both negative -> no valid result
        return false;


    pIntersect->IntersectionPoint = ray.getPointAtDistance(intersectionDist);
    pIntersect->Normal = (pIntersect->IntersectionPoint - m_Center).normalise();

    return true;
}

void CSphereSceneObject::setPosition(const vec3f& p)
{
    m_Center = p;
}

const vec3f & CSphereSceneObject::getPosition()
{
    return m_Center;
}

void CSphereSceneObject::setScale(const vec3f & p)
{
}

const vec3f & CSphereSceneObject::getScale()
{
    return vec3f();
}

void CSphereSceneObject::setRotation(const vec3f & p)
{
}

const vec3f & CSphereSceneObject::getRotation()
{
    return vec3f();
}

void CSphereSceneObject::setRadius(float r)
{
    m_Radius = r;
}

float CSphereSceneObject::getRadius()
{
    return m_Radius;
}

}//scene
}//raymond