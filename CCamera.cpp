#include "CCamera.h"

namespace raymond
{
namespace scene
{

CCamera::CCamera(const vec3f & eye, 
                 const vec3f & lookAt, 
                 const vec3f & up, 
                 u32 resX, 
                 u32 resY, 
                 f32 fov)
{
    m_eye = eye;
    f32 aspect = (f32)resY / (f32)resX;
    vec3f viewDir = lookAt - eye;
    vec3f u = viewDir.cross(up).normalise();
    vec3f v = u.cross(viewDir).normalise();

    //actually half of the viewplane width/heigth
    f32 viewPlaneW = maths::tangent(fov / 2.0f);
    f32 viewPlaneH = viewPlaneW*aspect;

    m_viewPlaneCorner = lookAt - (u*viewPlaneW) - (v*viewPlaneH);

    m_vecPerPixelX = (u*viewPlaneW * 2) / resX;
    m_vecPerPixelY = (v*viewPlaneH * 2) / resY;
}

ray3f CCamera::getRay(u32 pixelX, u32 pixelY)
{
    return ray3f(m_eye, m_viewPlaneCorner + (m_vecPerPixelX * pixelX) + (m_vecPerPixelY * pixelY));
}

} //scene
} //raymond