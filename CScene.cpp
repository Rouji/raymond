#include "CScene.h"

raymond::scene::CScene::CScene() :
    m_clearCol(0.0f)
{}

raymond::scene::CScene::~CScene()
{
    clear();
}

u32 raymond::scene::CScene::loadScene(const s8 * xmlPath)
{
    return 0;
}

void raymond::scene::CScene::addSceneObject(CSceneObject * pObj)
{
    m_objectList.push_back(pObj);
}

void raymond::scene::CScene::addLight(CLight * pLight)
{
    m_lightList.push_back(pLight);
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
    for (std::list<CSceneObject*>::iterator it = m_objectList.begin();
         it != m_objectList.end();
         it++)
    {
        delete *it;
    }
    m_objectList.clear();

    for (std::list<CLight*>::iterator it = m_lightList.begin();
    it != m_lightList.end();
        it++)
    {
        delete *it;
    }
    m_lightList.clear();
}
