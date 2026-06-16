#pragma once
#include "Entity.h"

#include <vector>
#include <map>
#include <algorithm>



class Scene
{
public:

    void AddToScene(Layers layer, Entity* rhs);

    void RemoveFromScene(Layers layer, Entity* rhs);

    void UpdateScene();

    void DrawScene();

    std::map<Layers, std::vector<Entity*>> renderables;
};