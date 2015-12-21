#include "PPMWriter.h"

#include "vec3.h"
#include "mat4.h"

using namespace raymond;

int main()
{
    vec3f a(1.0f,0.0f, 0.0f), b(0.0f,2.5f, 0.0f);
    mat4f m,n,o;
    m.setTranslation(vec3f(5.0f, 3.0f, 0.0f));
    n.setScale(vec3f(2.0f, 0.5f, 1.0f));
    vec3f translated = m.transform(a);
    vec3f combined = n.transform(translated);
    n *= m;
    vec3f matprodtest = n.transform(a);
    

	return 0;
}