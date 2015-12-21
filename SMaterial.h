#ifndef __SMATERIAL_H
#define __SMATERIAL_H

#include "col4.h"

namespace raymond
{

struct SMaterial
{
    //TODO: texture (file path? pointer to some cache in memory?)
    col4f Colour;
    float ka; //phong ambient component
    float kd; //phong diffuse component
    float ks; //phong specular component
    float exp; //phong cosine power for highlights
    float Reflectance;
    float Transmittance; 
    float Refraction; //index of refraction
};

} //raymond

#endif // !__SMATERIAL_H