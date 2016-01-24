#ifndef __TRIANGLE3_H
#define __TRIANGLE3_H

#include "types.h"
#include "vec3.h"
#include "ray3.h"

namespace raymond
{

enum ETriangleIntersection
{
    NONE = 0,
    ON_PLANE,
    INSIDE_TRIANGLE
};

template <class T>
class triangle3
{
public:
    vec3<T> A; vec3<T> B; vec3<T> C; //points of the triangle

    triangle3() {}

    triangle3(const vec3<T>& a, const vec3<T>& b, const vec3<T>& c) :
        A(a), B(b), C(c)
    {}

    bool operator==(const triangle3<T>& o) const
    {
        return o.A == A &&
               o.B == B &&
               o.C == C;
    }

    bool operator!=(const triangle3<T>& o) const
    {
        return !(*this == o)
    }

    //returns non-normalised normal
    vec3<T> getNormalFast() const
    {
        return (B-A).cross(C-A);
    }

    vec3<T> getNormal() const
    {
        return getNormalFast().normalise();
    }

    //intersect a ray with the plane of the triangle
    //return value indicates if an interection was found,
    //and whether it was inside the triangle or merely on
    //its plane
    //sets pOut to the point of intersection
    ETriangleIntersection intersect(const ray3<T>& ray, vec3<T>* pIntersect)
    {
        vec3<T> normal = getNormal();
        vec3<T> inter; //intersection point on plane
        T t1; T t2; T d;

        t2 = normal.dot(ray.getDirection());
        if (maths::equals(t2, 0.0f, FLOAT_ROUNDING_ERROR_32))
        {
            return false;
        }

        d = A.dot(normal);
        t1 = -(normal.dot(ray.getOrigin())) / t2;
        
        //intersection is behind the ray origin
        if (t1 < 0)
            return ETriangleIntersection::NONE;

        //get the intersection point on the plane
        inter = ray.getPointAtDistance(t1);

        //set out parameter
        if (pIntersect)
            *pIntersect = inter;

        //vectors from A to other 2 corners and the point
        vec3<T> AB = B - A;
        vec3<T> BC = C - B;
        vec3<T> CA = A - C;

        //vectors from corners to the point
        vec3<T> AP = inter - A;
        vec3<T> BP = inter - B;
        vec3<T> CP = inter - C;

        vec3<T> cross; //crossproduct of edge vector and point vector

        //check which side the point is on, for all 3 edges 
        cross = AB.cross(AP);
        if (normal.dot(cross) < 0)
            return ETriangleIntersection::ON_PLANE;
        cross = BC.cross(BP);
        if (normal.dot(cross) < 0)
            return ETriangleIntersection::ON_PLANE;
        cross = CA.cross(CP);
        if (normal.dot(cross) < 0)
            return ETriangleIntersection::ON_PLANE;

        return ETriangleIntersection::INSIDE_TRIANGLE;
    }

};

typedef triangle3<f32> triangle3f;

} //raymond

#endif // !__TRIANGLE3_H
