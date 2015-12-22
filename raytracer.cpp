#include "CPPMImageWriter.h"

#include "vec3.h"
#include "mat4.h"
#include "CSphere.h"
#include "CCamera.h"
#include "CSceneLoader.h"

using namespace raymond;

int main()
{
    //TODO: cmd parsing
    scene::CSceneLoader loader;
    scene::CScene* pScene = loader.loadXML("scenes/example2.xml");
    pScene->render();

    delete pScene;
	return 0;
}