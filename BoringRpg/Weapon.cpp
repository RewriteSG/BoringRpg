#include "Weapon.h"

Weapon::Weapon()
{
	DamageIncrease = 5;

}

Weapon::Weapon(Vector2 pos)
{
	DamageIncrease = 5;
	*GetPosition() = pos;
	SetObjectChar('W');
}

Weapon::Weapon(Vector2 pos, int setID)
{
	DamageIncrease = 5;
	*GetPosition() = pos;
	SetObjectChar('W');
	SetID(setID);
}

void Weapon::Start()
{

}


void Weapon::Update()
{
}

void Weapon::Collided()
{

}

int Weapon::GetDamageIncrease() const
{
	return DamageIncrease;
}
