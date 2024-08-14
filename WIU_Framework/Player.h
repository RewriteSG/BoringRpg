#pragma once
#include "Entity.h"
class Player :
    public Entity
{
   
public:
    static Player* playerInstance;

    Player();
    int x, y;
    void Start() override;
    void Update()override;
    void Collided(GameObject* collision) override;
    void OnDestroyed() override;
};

