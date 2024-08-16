#pragma once
#include "Entity.h"
#include "Player.h"
#include "TimeSystem.h"

class Robber :
    public Entity
{
    int steps;


public:
    bool IsRobberDead = false;
    static Robber* robberInstance;
    Robber();
    Robber(Vector2 toPos);
    

    int x, y;
    void Start() override;
    void Update()override;
    void Collided(GameObject* collision) override;
    void OnDestroyed() override;

   
    //positioning
   

    void MoveTowardsPlayer( Player& player);



};

