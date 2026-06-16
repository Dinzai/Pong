#include "Scene.h"


void Scene::AddToScene(Layers layer, Entity* rhs)
{
    renderables[layer].push_back(rhs);
}

void Scene::RemoveFromScene(Layers layer, Entity* rhs)
{
    auto& rendered = renderables[layer];
    rendered.erase(std::remove(rendered.begin(), rendered.end(), rhs), rendered.end());
}

void Scene::UpdateScene()
{
    
    for(auto [layer, rendered] : renderables)
    {
        for(Entity* obj : rendered)
        {
            obj->Update();
        }
    }
}

void Scene::DrawScene()
{
    for(auto [layer, rendered] : renderables)
    {
        for(Entity* obj : rendered)
        {
            obj->Render();
        }
    }
}