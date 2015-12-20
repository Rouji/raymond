#include "PPMWriter.h"

#include "vec3.h"
#include "mat4.h"
#include "Sphere.h"

using namespace raymond;

int main()
{
    io::PPMWriter out(500, 500);

    vec3f o(0.0f,0.0f, 0.0f), d(0.0f,0.0f, 1.0f);
    Sphere s;
    s.setPosition(vec3f(0.0f, 0.0f, 1000.0f));
    s.setRadius(250.0f);

    float inter;
    for (int i = 0; i < 500; i++)
    {
        for (int j = 0; j < 500; j++)
        {
            if (s.intersect(o + vec3f((float)(i-250), (float)(j - 250), 0.0f), d, &inter))
                out.SetPixel(i, j, (unsigned char)inter-750, (unsigned char)inter - 750, (unsigned char)inter - 750);
            else
                out.SetPixel(i, j, 0, 0, 0);
        }
    }

    out.Write("test.ppm");
	return 0;
}