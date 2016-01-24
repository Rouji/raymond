#ifndef __CMESH_H
#define __CMESH_H

#include <vector>

#include "vec2.h"
#include "vec3.h"
#include "triangle3.h"

namespace raymond
{

struct SFace
{
    u32 VertInd[3]; //indices to the three vertices
    u32 TexInd[3]; //indices to tex coords
    u32 NormInd[3]; //indices to normals
};

class CMesh
{
public:
    triangle3f getTriangle(u32 i) const
    {
        if (i < numFaces())
        {
            const SFace* f = &m_faces[i];
            return triangle3f(m_verts[f->VertInd[0]],
                              m_verts[f->VertInd[1]],
                              m_verts[f->VertInd[2]]);
        }
        //TODO: error log?
        return triangle3f();
    }

    triangle3f getNormals(u32 i) const
    {
        if (i < numFaces())
        {
            const SFace* f = &m_faces[i];
            return triangle3f(m_norms[f->NormInd[0]],
                              m_norms[f->NormInd[1]],
                              m_norms[f->NormInd[2]]);
        }
        //TODO: error log?
        return triangle3f();
    }

    const SFace* getFaces() const
    {
        return &m_faces[0];
    }

    const vec3f* getNormals() const
    {
        return &m_norms[0];
    }

    const vec3f* getVertices() const
    {
        return &m_verts[0];
    }

    u32 numFaces() const
    {
        return m_faces.size();
    }

    u32 numVertices() const
    {
        return m_verts.size();
    }

    //TODO: functions for texture coords

protected:
    std::vector<vec3f> m_verts;
    std::vector<vec3f> m_norms;
    std::vector<SFace> m_faces;
    std::vector<vec2f> m_texcoords;
};

}//raymond

#endif // !__CMESH_H
