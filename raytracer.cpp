#include "CSceneLoader.h"
#include "Log.h"

using namespace raymond;

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        io::LogError("You need to pass a valid XML file, e.g.:\n%s scenes/example2.xml\n", argv[0]);
        return 1;
    }

    scene::CSceneLoader loader;
    scene::CScene* pScene = loader.loadXML(argv[1]);
    
    if (pScene)
    {
        if (pScene->render())
        {
            io::LogError("Rendering the scene failed\n");
            delete pScene;
            return 2;
        }
        delete pScene;
        return 0;
	}

    io::LogError("Loading the scene failed\n");
    return 3;
}