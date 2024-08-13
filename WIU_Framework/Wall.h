#pragma once
#include "GameObject.h"
class Wall :
    public GameObject
{
public:
    Wall();
    Wall(Vector2 toPos);
};

