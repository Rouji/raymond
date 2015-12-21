#ifndef __CPPMIMAGEWRITER_H
#define __CPPMIMAGEWRITER_H

#include "types.h"

namespace raymond
{
namespace io
{

class CPPMImageWriter
{
public:
    CPPMImageWriter();
    CPPMImageWriter(u32 width, u32 height);
    ~CPPMImageWriter();

	//allocates a block of memory for width*heigth pixels
    //call first before doing anything else
    void Alloc(u32 width, u32 height);

    u32 SetPixel(u32 x, u32 y, u8 r, u8 g, u8 b);
    u32 Write(const char* path);

private:
    u8* m_pData;
    u32 m_uWidth;
    u32 m_uHeight;
};

}//io
}//raymond

#endif // !__CPPMIMAGEWRITER_H