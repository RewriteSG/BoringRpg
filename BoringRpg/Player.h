#pragma once
#include "Entity.h"
#include "Weapon.h"
class Player :
    public Entity
{

public:
    Player();
    void Start()override;
    void Update()override;
    void Collided(GameObject* collision) override;
    void OnDestroyed() override;
};

