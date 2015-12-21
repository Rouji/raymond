#include "CPPMImageWriter.h"

#include "vec3.h"
#include "mat4.h"
#include "CSphere.h"
#include "CCamera.h"
#include "CSceneLoader.h"

using namespace raymond;

int main()
{
    /*io::CPPMImageWriter out(dim2i(500, 400));

    vec3f eye(0.0f,0.0f, 0.0f), lookat(0.0f,0.0f, 1.0f), up(0.0f,1.0f,0.0f);
    scene::CSphere s;
    s.setPosition(vec3f(0.0f, 0.0f, 800.0f));
    s.setRadius(250.0f);

    scene::CCamera c(eye,
        lookat,
        up,
        dim2i(500,400));

    scene::SIntersection inter;
    for (int i = 0; i < 500; i++)
    {
        for (int j = 0; j < 400; j++)
        {
            if (s.intersect(c.getRay(vec2i(i, 400 - j)), &inter))
            {
                out.SetPixel(vec2i(i, j), col4f((inter.Normal + 1.0f)/2.0f));
            }
            else
                out.SetPixel(vec2i(i, j), col4f());
        }
    }

    out.Write("test.ppm");*/

    scene::CSceneLoader loader;
    scene::CScene* pScene = loader.loadXML("scenes/example2.xml");
    pScene->render();

    delete pScene;
	return 0;
}