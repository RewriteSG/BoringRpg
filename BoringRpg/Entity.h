#pragma once
#include "GameObject.h"
class Weapon;
class Entity :
    public GameObject
{
    int health;
    int attackDamage;
    int attackRange;
    Weapon* weaponHeld;

public :

    Entity();
    Entity(Vector2 toPos);

    void SetHealth(int toHealth);
    int GetHealth() const;
    void SetAttackDamage(int toAttackDamage);
    int GetAttackDamage() const;
    void SetAttackRange(int toAttackRange);
    int GetAttackRange() const;

    void Attack(GameObject* target) const;
    void Attack(Vector2 dir);

    Weapon* GetWeaponHeld() const;
    void SetWeaponHeld(Weapon*);
};

