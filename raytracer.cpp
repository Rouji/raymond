#include "PPMWriter.h"

#include "vec3.h"

int main()
{
    raymond::vec3<float> a(1.0f,0.0f, 0.0f), b(0.0f,1.0f, 0.0f);
    raymond::vec3<float> cross = a.cross(b);
    raymond::vec3<float> add = cross + a;
    add.setLength(10.0f);
	return 0;
}