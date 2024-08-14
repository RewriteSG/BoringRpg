#pragma once
#include "Entity.h"
class Player :
    public Entity
{

public:
    Player();
    int x, y;
    void Start() override;
    void Update()override;
    void Collided(GameObject* collision) override;
    void OnDestroyed() override;
};

