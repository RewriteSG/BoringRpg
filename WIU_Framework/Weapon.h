#pragma once
#include "Items.h"
class Weapon :
    public Item
{
    int DamageIncrease;

public:
    Weapon();
    Weapon(Vector2 pos);
    Weapon(Vector2 pos, int setID);
    void Start();
    void Update();
    void Collided();
    int GetDamageIncrease()const;
};

