#ifndef __CPPMIMAGEWRITER_H
#define __CPPMIMAGEWRITER_H

#include "types.h"
#include "vec2.h"
#include "col4.h"

namespace raymond
{
namespace io
{

class CPPMImageWriter
{
public:
    CPPMImageWriter();
    CPPMImageWriter(const dim2i& size);
    ~CPPMImageWriter();

	//allocates a block of memory for width*heigth pixels
    //call first before doing anything else
    void Alloc(const dim2i& size);

    u32 SetPixel(const vec2i& pos, const col4f& col);
    u32 Write(const char* path);

private:
    u8* m_pData;
    dim2i m_size;
};

}//io
}//raymond

#endif // !__CPPMIMAGEWRITER_H