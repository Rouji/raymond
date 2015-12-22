#ifndef __CLIGHT_H
#define __CLIGHT_H

#include "col4.h"
#include "vec3.h"
#include "SMaterial.h"

namespace raymond
{
namespace scene
{

class CLight
{
public:
    enum LightType
    {
        LIGHT_AMBIENT = 0,
        LIGHT_PARALLEL,
        LIGHT_POINT,
        LIGHT_SPOT
    };

    CLight() : 
        Type(LIGHT_AMBIENT),
        Colour(col4f()),
        Position(vec3f(0.0f)),
        Direction(vec3f(1.0f,0.0f,0.0f)),
        FalloffAlpha1(0.0f),
        FalloffAlpha2(0.0f)
    {}

    ~CLight(){}

    col4f shade(const vec3f& point, const vec3f& normal, const vec3f& eye, const SMaterial& mat);

    LightType Type;
    col4f Colour;
    vec3f Position;
    vec3f Direction;
    f32 FalloffAlpha1;
    f32 FalloffAlpha2;
};

}//scene
}//raymond

#endif // !__CLIGHT_H

