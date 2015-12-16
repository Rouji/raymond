#include "PPMWriter.h"

#include <stdio.h>
#include <stdlib.h>
#include <new>

PPMWriter::PPMWriter() : 
    m_pData(0),
    m_uWidth(0),
    m_uHeight(0)
{}

PPMWriter::PPMWriter(unsigned int width, unsigned int height) : 
    m_pData(0)
{
    Alloc(width, height);
}

PPMWriter::~PPMWriter()
{
    if (m_pData)
        delete[] m_pData;
}

void PPMWriter::Alloc(unsigned int width, unsigned int height)
{
    if (m_pData)
        delete[] m_pData;

    m_uWidth = width;
    m_uHeight = height;
    m_pData = new unsigned char[width*height*3];
}

unsigned int PPMWriter::SetPixel(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b)
{
    if (!m_pData || x > m_uWidth || y > m_uHeight)
        return 1;

    unsigned int pixelInd = x*3 + (m_uWidth * y * 3);
    m_pData[pixelInd] = r;
    m_pData[pixelInd+1] = g;
    m_pData[pixelInd+2] = b;

    return 0;
}

unsigned int PPMWriter::Write(const char* path)
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
    for (unsigned int i = 0; i < m_uHeight; ++i)
    {
        for (unsigned int j = 0; j < m_uWidth; ++j)
        {
            unsigned int pixelInd = j*3+(i*m_uWidth*3);
            len = sprintf(buff, "%d %d %d ", m_pData[pixelInd], m_pData[pixelInd+1],m_pData[pixelInd+2]);
            fwrite(buff,len,1,pFile);
        }
        fwrite("\n",1,1,pFile);
    }

    return 0;
}