#ifndef __MATERIAL_H
#define __MATERIAL_H

#include "col4.h"

namespace raymond
{

class Material
{
public:
    Material() {}
    ~Material() {}

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

#endif // !__MATERIAL_H