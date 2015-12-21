#ifndef __SMATERIAL_H
#define __SMATERIAL_H

#include "col4.h"

namespace raymond
{

struct SMaterial
{
    //TODO: texture (file path? pointer to some cache in memory?)
    col4f Colour;
    f32 ka; //phong ambient component
    f32 kd; //phong diffuse component
    f32 ks; //phong specular component
    f32 exp; //phong cosine power for highlights
    f32 Reflectance;
    f32 Transmittance; 
    f32 Refraction; //index of refraction
};

} //raymond

#endif // !__SMATERIAL_H