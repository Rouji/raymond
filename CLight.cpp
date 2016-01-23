#include "CLight.h"


namespace raymond
{
namespace scene
{

col4f CLight::shade(const vec3f& point, const vec3f& normal, const vec3f& eye, const SMaterial& mat)
{
    vec3f vecLight;
    vec3f vecRefl;
    vec3f vecEye;
    f32 Fa;
    f32 Fd;
    f32 Fs;
    col4f baseColour = mat.Colour * Colour;

    if (Type == LIGHT_AMBIENT)
    {
        Fa = mat.ka;
        return baseColour * Fa;
    }
    else if (Type == LIGHT_PARALLEL)
    {
        vecEye = (eye - point).normalise();
        vecLight = (-Direction).normalise();
        vecRefl = vecLight.mirrorAlongNormal(normal);

        Fd = maths::clamp(normal.dot(vecLight) * mat.kd, 0.0f, 1.0f);
        Fs = maths::clamp(maths::powf(vecRefl.dot(vecEye), mat.exp) * mat.ks, 0.0f, 1.0f);
        return (baseColour*Fd) + col4f(Fs, Fs, Fs, Fs);
    }
    else if (Type == LIGHT_POINT ||
             Type == LIGHT_SPOT)
    {
        //TODO
        //vecLight = (Position - point).normalise();
    }
    
    return col4f(0.0f);
}

} //scene
} //raymond

