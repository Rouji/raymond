#include "CSphere.h"

namespace raymond
{
namespace scene
{

//ray-sphere intersection test based on a geometric approach
//TODO: implement a quadratic equation -variant instead?
bool CSphere::intersect(const ray3f& ray, SIntersection* pIntersect)
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

    //offset the intersection point slightly from the sphere to avoid rounding errors
    //putting us inside the sphere
    pIntersect->IntersectionPoint += pIntersect->Normal * FLOAT_ROUNDING_ERROR_32; 

    return true;
}

CSphere& CSphere::setPosition(const vec3f& p)
{
    m_Center = p;
    return *this;
}

const vec3f & CSphere::getPosition()
{
    return m_Center;
}

CSphere & CSphere::setRadius(float r)
{
    m_Radius = r;
    return *this;
}

float CSphere::getRadius()
{
    return m_Radius;
}

}//scene
}//raymond