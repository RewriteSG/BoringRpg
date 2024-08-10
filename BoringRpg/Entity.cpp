#include "Entity.h"
#include <iostream>
#include "ObjectManager.h"
Entity::Entity() : health(0), attackDamage(0), attackRange(0)
{

	weaponHeld = nullptr;
}

Entity::Entity(Vector2 toPos) : health(0), attackDamage(0), attackRange(0)
{
	weaponHeld = nullptr;
	*GetPosition() = toPos;
}

void Entity::SetHealth(int toHealth)
{
	health = toHealth;
}

int Entity::GetHealth() const
{
	return health;
}

void Entity::SetAttackDamage(int toAttackDamage)
{
	attackDamage = toAttackDamage;
}

int Entity::GetAttackDamage() const
{
	return attackDamage;
}

void Entity::SetAttackRange(int toAttackRange)
{
	attackRange = toAttackRange;
}

int Entity::GetAttackRange() const
{
	return attackRange;
}


void Entity::Attack(GameObject* target) const
{
	Entity* targetEntity = dynamic_cast<Entity*>(target);
	if (targetEntity)
	{
		//std::cout << " Is Attacked";
		targetEntity->health -= attackDamage;
		if (targetEntity->health <= 0)
			ObjectManager::getObjectManager()->DestroyObject(target);
	}
}

void Entity::Attack(Vector2 dir)
{
	Vector2 reset = dir;
	for (int i = 1; i <= attackRange; i++)
	{
		dir *= i;
		dir += *GetPosition();
		if (ObjectManager::getObjectManager()->GetObjectAtPosition(dir)) 
		{
			Attack(ObjectManager::getObjectManager()->GetObjectAtPosition(dir));
			break;
		}
		dir = reset;
	}
}

Weapon* Entity::GetWeaponHeld() const
{
	return weaponHeld;
}

void Entity::SetWeaponHeld(Weapon* wep)
{
	weaponHeld = wep;
}
