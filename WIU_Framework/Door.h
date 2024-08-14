#pragma once
#include "Items.h"
class Door :
    public Item
{
public:
    enum TypeOfDoor 
    {
        ClosetDoor,
        BathroomDoor,
        MainDoor,
        KitchenDoor,
        BedroomDoor
    };
    TypeOfDoor door;
    Door(TypeOfDoor type, Vector2 toPos);
    void Collided(GameObject* obj) override;
};

