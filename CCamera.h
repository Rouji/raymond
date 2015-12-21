#ifndef __CCAMERA_H
#define __CCAMERA_H

#include "ray3.h"
#include "mat4.h"
#include "vec3.h"
#include "vec2.h"
#include "maths.h"

namespace raymond
{
namespace scene
{

class CCamera
{
public:
    //fov assumed to be horizontal
    CCamera(const vec3f& eye = vec3f(0.0f), 
            const vec3f& lookAt = vec3f(1.0f, 0.0f, 0.0f), 
            const vec3f& up = vec3f(0.0f, 1.0f, 0.0f), 
            const dim2i& size = dim2i(512,512), 
            f32 fov = PI / 2.0f,
            u32 maxBounces = 5);

    //return a ray for a given screen pixel
    ray3f getRay(const vec2i& pos);

    void setEyePoint(const vec3f& eye);
    void setLookAtPoint(const vec3f& lookAt);
    void setUpVector(const vec3f& up);
    void setImageSize(const dim2i& size);
    void setFOV(f32 fov);
    void setMaxBounces(u32 maxBounces);

    const vec3f& getEyePoint() const;
    const vec3f& getLookAtPoint() const;
    const vec3f& getUpVector() const;
    const dim2i& getImageSize() const;
    f32 getFOV() const;
    u32 getMaxBounces() const;

private:
    //(re)compute parameters needed form pixel rays
    void computePlane();
    bool m_dirty; //true -> needs to be recomputed

    vec3f m_eye;
    vec3f m_lookAt;
    vec3f m_up;
    dim2i m_imageSize;
    f32 m_fov;
    vec3f m_viewPlaneCorner; //bottom-left corner of view plane
    vec3f m_vecPerPixelX; //vector to add to a point on the view plane to get to ne next pixel along x
    vec3f m_vecPerPixelY; //vector to add to a point on the view plane to get to ne next pixel along y
    u32 m_maxBounces; //max bounces for each ray
};

} //scene
} //raymond

#endif // !__CCAMERA_H

