#include "CScene.h"

raymond::scene::CScene::CScene() :
    m_clearCol(0.0f),
    m_pCamera(0)
{}

raymond::scene::CScene::~CScene()
{
    clear();
}

void raymond::scene::CScene::addSceneObject(CSceneObject * pObj)
{
    m_objectList.push_back(pObj);
}

void raymond::scene::CScene::addLight(CLight * pLight)
{
    m_lightList.push_back(pLight);
}

void raymond::scene::CScene::setCamera(CCamera * pCam)
{
    //delete old camera object
    if (m_pCamera)
        delete m_pCamera;

    m_pCamera = pCam;
}

void raymond::scene::CScene::setClearColour(const col4f& col)
{
    m_clearCol = col;
}

void raymond::scene::CScene::setImagePath(const s8 * path)
{
    m_imagePath = path;
}

u32 raymond::scene::CScene::render()
{
    //TODO: render-magic.
    return 0;
}

void raymond::scene::CScene::clear()
{
    //clear objects
    for (std::list<CSceneObject*>::iterator it = m_objectList.begin();
         it != m_objectList.end();
         it++)
    {
        delete *it;
    }
    m_objectList.clear();

    //clear lights
    for (std::list<CLight*>::iterator it = m_lightList.begin();
    it != m_lightList.end();
        it++)
    {
        delete *it;
    }
    m_lightList.clear();

    //delete camera
    if (m_pCamera)
        delete m_pCamera;
}
