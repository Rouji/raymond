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
    if (!m_pMesh || m_faces.empty() || m_normals.empty())
        return false;

    u32 nearestInd = -1;
    f32 nearestSquared = 0;
    f32 distSquared = 0;
    vec3f inter;

    for (u32 i = 0; i < m_faces.size(); ++i)
    {
        if (m_faces[i].intersect(ray, &inter) == INSIDE_TRIANGLE)
        {
            distSquared = ray.getOrigin().distanceSquared(inter);
            if (nearestInd == -1 || distSquared < nearestSquared)
            {
                pIntersect->IntersectionPoint = inter;
                pIntersect->Normal = m_normals[i];
                nearestSquared = distSquared;
                nearestInd = i;
            }
        }
    }

    if (nearestInd == -1)
        return false;

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

    for (u32 i = 0; i < m_pMesh->numFaces(); ++i)
    {
        triangle3f t = m_pMesh->getTriangle(i);
        m_faces.push_back(t);
        m_normals.push_back(t.getNormal());
    }
}


}
}
