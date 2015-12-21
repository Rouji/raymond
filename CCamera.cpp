#include "CCamera.h"

namespace raymond
{
namespace scene
{

CCamera::CCamera(const vec3f& eye, 
                 const vec3f& lookAt, 
                 const vec3f& up, 
                 const dim2i& size,
                 f32 fov,
                 u32 maxBounces) :
    m_eye(eye),
    m_lookAt(lookAt),
    m_up(up),
    m_imageSize(size),
    m_fov(fov),
    m_maxBounces(maxBounces),
    m_dirty(true)
{}

ray3f CCamera::getRay(const vec2i& pos)
{
    if (m_dirty)
        computePlane();

    vec3f planeCoord = (m_vecPerPixelX * pos.X) + (m_vecPerPixelY * (m_imageSize.Y - pos.Y));
    vec3f worldCoord = m_viewPlaneCorner + planeCoord;
    vec3f dir = worldCoord - m_eye;
    return ray3f(m_eye, dir);
}

void CCamera::setEyePoint(const vec3f & eye)
{
    m_eye = eye; 
    m_dirty = true;
}

void CCamera::setLookAtPoint(const vec3f & lookAt)
{
    m_lookAt = lookAt;
    m_dirty = true;
}

void CCamera::setUpVector(const vec3f & up)
{
    m_up = up;
    m_dirty = true;
}

void CCamera::setImageSize(const dim2i & size)
{
    m_imageSize = size;
    m_dirty = true;
}

void CCamera::setFOV(f32 fov)
{
    m_fov = fov;
    m_dirty = true;
}

void CCamera::setMaxBounces(u32 maxBounces)
{
    m_maxBounces = maxBounces;
    m_dirty = true;
}

const vec3f & CCamera::getEyePoint() const
{
    return m_eye;
}

const vec3f & CCamera::getLookAtPoint() const
{
    return m_lookAt;
}

const vec3f & CCamera::getUpVector() const
{
    return m_up;
}

const dim2i & CCamera::getImageSize() const
{
    return m_imageSize;
}

f32 CCamera::getFOV() const
{
    return m_fov;
}

u32 CCamera::getMaxBounces() const
{
    return m_maxBounces;
}

void CCamera::computePlane()
{
    f32 aspect = (f32)m_imageSize.Y / (f32)m_imageSize.X;
    vec3f viewDir = (m_lookAt - m_eye).normalise();
    vec3f u = viewDir.cross(m_up).normalise();
    vec3f v = u.cross(viewDir).normalise();

    //actually half of the viewplane width/heigth
    f32 viewPlaneW = maths::tangent(m_fov / 2.0f);
    f32 viewPlaneH = viewPlaneW*aspect;

    //m_viewPlaneCorner = m_lookAt - (u*viewPlaneW) - (v*viewPlaneH);
    m_viewPlaneCorner = (m_eye + viewDir) - (u*viewPlaneW) - (v*viewPlaneH);

    m_vecPerPixelX = (u*viewPlaneW * 2) / m_imageSize.X;
    m_vecPerPixelY = (v*viewPlaneH * 2) / m_imageSize.Y;
    m_dirty = false;
}

} //scene
} //raymond