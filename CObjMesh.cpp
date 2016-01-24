#include "CObjMesh.h"
#include "Log.h"

#include <stdio.h>

namespace raymond
{

u32 CObjMesh::load(const char * path)
{
    FILE* pFile;
    if (!path)
    {
        io::LogError("[CObjMesh] Got zero-pointer for a path\n");
        return 1;
    }

    if (!(pFile = fopen(path, "r")))
    {
        io::LogError("[CObjMesh] Could not open file '%s'\n", path);
        return 2;
    }

    m_faces.clear();
    m_norms.clear();
    m_texcoords.clear();
    m_verts.clear();

    char lineBuffer[1024];
    size_t len = 0;
    size_t read = 0;
    vec3f vert;
    vec3f norm;
    vec2f tex;
    SFace face;
    memset(lineBuffer, 0, 1024);

    while (fgets(lineBuffer,1024,pFile))
    {
        switch (lineBuffer[0])
        {
        case '#':
        case '$':
            continue;
        case 'f': //faces
            //TODO: tex/norm -less faces
            //TODO: quads
            sscanf(lineBuffer + 2, "%d/%d/%d %d/%d/%d %d/%d/%d", &face.VertInd[0], &face.TexInd[0], &face.NormInd[0],
                &face.VertInd[1], &face.TexInd[1], &face.NormInd[1],
                &face.VertInd[2], &face.TexInd[2], &face.NormInd[2]);
            m_faces.push_back(face);
            break;
        case 'v':
            if (lineBuffer[1] == ' ') //vertex
            {
                sscanf(lineBuffer + 2, "%f %f %f", &vert.X, &vert.Y, &vert.Z);
                m_verts.push_back(vert);
            }
            else if (lineBuffer[1] == 'n') //normal
            {
                sscanf(lineBuffer + 3, "%f %f %f", &norm.X, &norm.Y, &norm.Z);
                m_norms.push_back(norm);
            }
            else if (lineBuffer[1] == 't') //tex coord
            {
                sscanf(lineBuffer + 3, "%f %f", &tex.X, &tex.Y);
                m_texcoords.push_back(tex);
            }
            break;
        }
    }
}

}