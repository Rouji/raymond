#include "CPPMImageWriter.h"

#include <stdio.h>
#include <stdlib.h>
#include <new>

namespace raymond
{
namespace io
{

CPPMImageWriter::CPPMImageWriter() : 
    m_pData(0),
    m_size(0)
{}

CPPMImageWriter::CPPMImageWriter(const dim2i& size) :
    m_pData(0)
{
    Alloc(size);
}

CPPMImageWriter::~CPPMImageWriter()
{
    if (m_pData)
        delete[] m_pData;
}

void CPPMImageWriter::Alloc(const dim2i& size)
{
    if (m_pData)
        delete[] m_pData;

    m_size = size;
    m_pData = new u8[size.X*size.Y*3];
}

u32 CPPMImageWriter::SetPixel(const vec2i& pos, const col4f& col)
{
    if (!m_pData || pos.X > m_size.X || pos.Y > m_size.Y)
        return 1;

    col4f tmpCol = col * 255.0f;

    tmpCol.clamp(0.0f, 255.0f);

    u32 pixelInd = pos.X*3 + (pos.Y * m_size.X * 3);
    m_pData[pixelInd] = (u8)tmpCol.R;
    m_pData[pixelInd+1] = (u8)tmpCol.G;
    m_pData[pixelInd+2] = (u8)tmpCol.B;

    return 0;
}

u32 CPPMImageWriter::Write(const char* path)
{
    if (!m_pData)
        return 1;

    FILE* pFile = fopen(path, "wb");
    if (!pFile)
        return 2;

    char buff[128];

    int len = sprintf(buff,"%d %d\n",m_size.X,m_size.Y);

    fwrite("P3\n",3,1,pFile);
    fwrite(buff,len,1,pFile);
    fwrite("255\n",4,1,pFile);
    for (u32 y = 0; y < m_size.Y; ++y)
    {
        for (u32 x = 0; x < m_size.X; ++x)
        {
            u32 pixelInd = x*3+(y*m_size.X*3);
            len = sprintf(buff, "%d %d %d ", m_pData[pixelInd], m_pData[pixelInd+1],m_pData[pixelInd+2]);
            fwrite(buff,len,1,pFile);
        }
        fwrite("\n",1,1,pFile);
    }

    return 0;
}


} //io
} //raymond