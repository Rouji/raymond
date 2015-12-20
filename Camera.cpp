#include "Camera.h"

namespace raymond
{

Camera::Camera(const vec3f & eye, const vec3f & lookAt, const vec3f & up, float fov, unsigned int resX, unsigned int resY)
{
    m_eye = eye;
    float aspect = (float)resY / (float)resY;
    vec3f viewDir = lookAt - eye;
    vec3f u = viewDir.cross(up).normalise();
    vec3f v = u.cross(viewDir).normalise();

    //actually half of the viewplane width/heigth
    float viewPlaneW = maths::tangent(fov / 2.0f);
    float viewPlaneH = viewPlaneW*aspect;

    m_viewPlaneCorner = lookAt - (u*viewPlaneW) - (v*viewPlaneH);

    m_vecPerPixelX = (u*viewPlaneW * 2) / resX;
    m_vecPerPixelY = (v*viewPlaneH * 2) / resY;
}

ray3f Camera::getRay(unsigned int pixelX, unsigned int pixelY)
{

    return ray3f(m_eye, m_viewPlaneCorner + (m_vecPerPixelX * pixelX) + (m_vecPerPixelY * pixelY));
}


} //raymond