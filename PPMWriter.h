class PPMWriter
{
public:
    PPMWriter();
    PPMWriter(unsigned int width, unsigned int height);
    ~PPMWriter();

	//allocates 
    void Alloc(unsigned int width, unsigned int height);
    unsigned int SetPixel(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b);
    unsigned int Write(const char* path);

private:
    unsigned char* m_pData;
    unsigned int m_uWidth;
    unsigned int m_uHeight;
};