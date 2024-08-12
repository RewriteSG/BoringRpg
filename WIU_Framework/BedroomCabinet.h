#pragma once
#include "Items.h"
class BedroomCabinet :
    public Item
{
    void Start() override;
    void Update() override;
    void Collided(GameObject* obj) override;
};

