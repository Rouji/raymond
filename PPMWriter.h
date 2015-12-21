#ifndef __PPMWRITER_H
#define __PPMWRITER_H


namespace raymond
{
namespace io
{

class PPMWriter
{
public:
    PPMWriter();
    PPMWriter(unsigned int width, unsigned int height);
    ~PPMWriter();

	//allocates a block of memory for width*heigth pixels
    //call first before doing anything else
    void Alloc(unsigned int width, unsigned int height);

    unsigned int SetPixel(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b);
    unsigned int Write(const char* path);

private:
    unsigned char* m_pData;
    unsigned int m_uWidth;
    unsigned int m_uHeight;
};

}//io
}//raymond

#endif // !__PPMWRITER_H