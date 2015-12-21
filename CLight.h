#ifndef __CLIGHT_H
#define __CLIGHT_H

#include "col4.h"
#include "vec3.h"

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
        Direction(vec3f(0.0f)),
        FalloffAlpha1(0.0f),
        FalloffAlpha2(0.0f)
    {}

    ~CLight(){}

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

