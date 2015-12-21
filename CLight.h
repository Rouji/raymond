#ifndef __CLIGHT_H
#define __CLIGHT_H

#include "col4.h"
#include "vec3.h"

namespace raymond
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
        Direction(vec3f(0.0f)),
        FalloffAlpha1(0.0f),
        FalloffAlpha2(0.0f)
    {}

    ~CLight(){}

    LightType Type;
    col4f Colour;
    vec3f Position;
    vec3f Direction;
    float FalloffAlpha1;
    float FalloffAlpha2;
};

}

#endif // !__CLIGHT_H
