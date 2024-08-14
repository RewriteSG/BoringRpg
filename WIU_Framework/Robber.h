#pragma once
#include "Entity.h"
#include "Player.h"
#include "TimeSystem.h"
class Robber :
    public Entity
{
    int steps;
    Vector2 position;

public:

    TimeSystem TimerForRobberSteps;

    Robber();
    Robber(Vector2 toPos);


    void Start() override;
    void Update()override;
    void Collided(GameObject* collision) override;
    void OnDestroyed() override;

    //positioning

   // Robber(Vector2 startPos) : position(startPos) {}
   /* Vector2 GetPosition() const;
    void MoveTowardsPlayer(const Player& player);*/

};

