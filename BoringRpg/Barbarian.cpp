#include "Barbarian.h"
#include <iostream>

Barbarian::Barbarian()
{
	SetHealth(rand() % (100 - 80) + 80);
	SetAttackRange(1);
	SetAttackDamage(rand() % (20 - 10) + 10);
	SetObjectChar('B');
}
