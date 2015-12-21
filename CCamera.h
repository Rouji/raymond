#ifndef __CCAMERA_H
#define __CCAMERA_H

#include "ray3.h"
#include "mat4.h"
#include "vec3.h"
#include "maths.h"

namespace raymond
{
namespace scene
{

class CCamera
{
public:
    //fov assumed to be horizontal
    CCamera(const vec3f& eye = vec3f(0), 
            const vec3f& lookAt = vec3f(1.0f, 0, 0), 
            const vec3f& up = vec3f(0, 1.0f, 0), 
            u32 resX = 512, 
            u32 resY = 512, 
            f32 fov = PI / 2.0f);

    //return a ray for a given screen pixel
    ray3f getRay(unsigned int pixelX, unsigned int pixelY);

private:
    vec3f m_eye;
    vec3f m_lookAt;
    vec3f m_up;
    u32 m_resX;
    u32 m_resY;
    f32 m_fov;
    vec3f m_viewPlaneCorner; //bottom-left corner of view plane
    vec3f m_vecPerPixelX; //vector to add to a point on the view plane to get to ne next pixel along x
    vec3f m_vecPerPixelY; //vector to add to a point on the view plane to get to ne next pixel along y
};

} //scene
} //raymond

#endif // !__CCAMERA_H

