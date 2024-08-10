#pragma once
#include "Entity.h"
class GameManager;
class Goblin :
    public Entity
{
    GameManager* gm;
public:
    Goblin();
    Goblin(Vector2 pos);
    Goblin(Vector2 pos, int setId);
    void Start() override;
    void Update() override;
    void OnDestroyed() override;
};

