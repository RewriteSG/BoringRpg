#pragma once
#include "Entity.h"

class Player :
    public Entity
{
private:
    Vector2 position;
public:
    Player();
    void Start() override;
    void Update()override;
    void Collided(GameObject* collision) override;
    void OnDestroyed() override;


    //positioning
    Player(Vector2 startPos) : position(startPos) {}
    Vector2 GetPosition() const;
    void SetPosition(Vector2 newPos);
};

