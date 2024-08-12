#pragma once
#include "GameObject.h"
class Weapon;
class Entity : public GameObject
{
    int health;

public :

    Entity();
    Entity(Vector2 toPos);

    void SetHealth(int toHealth);
    int GetHealth() const; 

};

