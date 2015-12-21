#include "PPMWriter.h"

#include "vec3.h"
#include "mat4.h"
#include "Sphere.h"
#include "Camera.h"

using namespace raymond;

int main()
{
    io::PPMWriter out(500, 400);

    vec3f eye(0.0f,0.0f, 0.0f), lookat(0.0f,0.0f, 1.0f), up(0.0f,1.0f,0.0f);
    Sphere s;
    s.setPosition(vec3f(0.0f, 0.0f, 800.0f));
    s.setRadius(250.0f);

    Camera c(eye,
        lookat,
        up,
        500,
        400);

    Intersection inter;
    for (int i = 0; i < 500; i++)
    {
        for (int j = 0; j < 400; j++)
        {
            if (s.intersect(c.getRay(i, 400 - j), &inter))
            {
                out.SetPixel(i, j, (inter.Normal.X + 1.0f) * 125, (inter.Normal.Y + 1.0f) * 125, (inter.Normal.Z + 1.0f) * 125);
            }
            else
                out.SetPixel(i, j, 0, 0, 0);
        }
    }

    out.Write("test.ppm");
	return 0;
}