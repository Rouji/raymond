#include "CMeshSceneObject.h"

namespace raymond
{
namespace scene
{


CMeshSceneObject::CMeshSceneObject() : m_pMesh(0), m_pos(0.0f,0.0f,0.0f)
{
}

CMeshSceneObject::~CMeshSceneObject()
{
    delete m_pMesh;
}

bool CMeshSceneObject::intersect(const ray3f & ray, SIntersection * pIntersect)
{
    if (!m_pMesh)
        return false;

    vec3f inter;
    vec3f tmp;
    f32 lastDistSquared = 0.0f;
    f32 newDistSquared = 0.0f;
    u32 found = -1;
    for (u32 i = 0; i < m_pMesh->numFaces(); ++i)
    {
        if ((m_pMesh->getTriangle(i)+m_pos).intersect(ray, &tmp) == ETriangleIntersection::INSIDE_TRIANGLE &&
            (found == -1 || (newDistSquared = ray.getOrigin().distanceSquared(tmp)) < lastDistSquared))
        {
            found = i;
            lastDistSquared = newDistSquared;
            inter = tmp;
        }
    }

    if (found == -1)
        return false;

    pIntersect->IntersectionPoint = inter;
    pIntersect->Normal = m_pMesh->getNormals(found).A;

    return true;
}

void CMeshSceneObject::setPosition(const vec3f & p)
{
    m_pos = p;
}

const vec3f & CMeshSceneObject::getPosition()
{
    return m_pos;
}

void CMeshSceneObject::setScale(const vec3f & p)
{
}

const vec3f & CMeshSceneObject::getScale()
{
    return vec3f();
}

void CMeshSceneObject::setRotation(const vec3f & p)
{
}

const vec3f & CMeshSceneObject::getRotation()
{
    return vec3f();
}

void CMeshSceneObject::setMesh(CMesh * pMesh)
{
    m_pMesh = pMesh;
}


}
}