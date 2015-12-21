#include "CSceneLoader.h"
#include "Log.h"

using namespace raymond;

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        io::LogError("You need to pass a valid XML file, e.g.:\n%s scenes/example2.xml\n", argv[0]);
        return 0;
    }

    scene::CSceneLoader loader;
    scene::CScene* pScene = loader.loadXML("scenes/example2.xml");
    
    if (pScene)
    {
        pScene->render();
        delete pScene;
        return 0;
	}

    io::LogError("Rendering the scene failed\n");
    return 1;
}