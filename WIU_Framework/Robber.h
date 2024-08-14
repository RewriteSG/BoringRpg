#pragma once
#include "Entity.h"
class Robber :
    public Entity
{
    int steps;


public:
    Robber();
    Robber(Vector2 toPos);


    void Start() override;
    void Update()override;
    void Collided(GameObject* collision) override;
    void OnDestroyed() override;

};

