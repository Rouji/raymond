#include "CSphere.h"

namespace raymond
{


//ray-sphere intersection test based on a geometric approach
//TODO: implement a quadratic equation -variant instead?
bool Sphere::intersect(const ray3f& ray, SIntersection* pIntersect)
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


    pIntersect->Inter = intersectionDist;
    pIntersect->Normal = (ray.getPointAtDistance(intersectionDist) - m_Center).normalise();

    return true;
}

Sphere& Sphere::setPosition(const vec3f& p)
{
    m_Center = p;
    return *this;
}

const vec3f & Sphere::getPosition()
{
    return m_Center;
}

Sphere & Sphere::setRadius(float r)
{
    m_Radius = r;
    return *this;
}

float Sphere::getRadius()
{
    return m_Radius;
}

}//raymond