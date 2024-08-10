#include "Archer.h"
#include <iostream>
Archer::Archer()
{
	SetHealth(rand() % (80 - 60) + 60);
	SetAttackRange(2);
	SetAttackDamage(rand() % (10 - 1) + 1);
	SetObjectChar('A');
}
