#ifndef __COBJMESH_H
#define __COBJMESH_H

#include "types.h"
#include "CMesh.h"

namespace raymond
{

class CObjMesh : public CMesh
{
public:
    u32 load(const char* path);
};

}

#endif // !__COBJMESH_H
