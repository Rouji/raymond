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
    m_uWidth(0),
    m_uHeight(0)
{}

CPPMImageWriter::CPPMImageWriter(u32 width, u32 height) : 
    m_pData(0)
{
    Alloc(width, height);
}

CPPMImageWriter::~CPPMImageWriter()
{
    if (m_pData)
        delete[] m_pData;
}

void CPPMImageWriter::Alloc(u32 width, u32 height)
{
    if (m_pData)
        delete[] m_pData;

    m_uWidth = width;
    m_uHeight = height;
    m_pData = new u8[width*height*3];
}

u32 CPPMImageWriter::SetPixel(u32 x, u32 y, u8 r, u8 g, u8 b)
{
    if (!m_pData || x > m_uWidth || y > m_uHeight)
        return 1;

    u32 pixelInd = x*3 + (m_uWidth * y * 3);
    m_pData[pixelInd] = r;
    m_pData[pixelInd+1] = g;
    m_pData[pixelInd+2] = b;

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

    int len = sprintf(buff,"%d %d\n",m_uWidth,m_uHeight);

    fwrite("P3\n",3,1,pFile);
    fwrite(buff,len,1,pFile);
    fwrite("255\n",4,1,pFile);
    for (u32 i = 0; i < m_uHeight; ++i)
    {
        for (u32 j = 0; j < m_uWidth; ++j)
        {
            u32 pixelInd = j*3+(i*m_uWidth*3);
            len = sprintf(buff, "%d %d %d ", m_pData[pixelInd], m_pData[pixelInd+1],m_pData[pixelInd+2]);
            fwrite(buff,len,1,pFile);
        }
        fwrite("\n",1,1,pFile);
    }

    return 0;
}


} //io
} //raymond