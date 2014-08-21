#include "ad/Scene.h"

namespace ad {

Scene::Scene(std::string FileName)
{
    RootGameobject = new ad::Gob(NULL, "ROOT");
    fileName = FileName;
}

Scene::~Scene()
{
    delete RootGameobject;
}

void Scene::Update()
{
    RootGameobject->Update();
}

} // namespace ad
