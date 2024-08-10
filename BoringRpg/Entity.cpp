#include "Entity.h"
#include <iostream>
#include "ObjectManager.h"
Entity::Entity() : health(0)
{

}

Entity::Entity(Vector2 toPos) : health(0)
{
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
