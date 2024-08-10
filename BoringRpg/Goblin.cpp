#include "Goblin.h"
#include "GameManager.h"
Goblin::Goblin()
{
	Start();
}
Goblin::Goblin(Vector2 pos)
{
	*GetPosition() = pos;
	Start();
}
Goblin::Goblin(Vector2 pos, int setId)
{
	*GetPosition() = pos;
	SetObjectChar('0'+setId);
	Start();
}
void Goblin::Start()
{
	SetHealth(20);
	SetAttackDamage(5);
	SetAttackRange(1);
}
void Goblin::Update()
{
	if (GameManager::getGM()->GetPlayerTurn())
		return;
	if (!GameManager::getGM()->GetPlayer())
		return;
	int randomDirection = 0;
	Vector2 dir;
	if (Vector2::Distance(*GetPosition(), *GameManager::getGM()->GetPlayer()->GetPosition()) <= 1)
	{
		Attack(GameManager::getGM()->GetPlayer());
		
	}
	else
	{
		randomDirection = rand() % 4;
		switch (randomDirection)
		{
		case 0: // up
			dir.SetXandY(0, -1);
			break;
		case 1: // down
			dir.SetXandY(0, 1);
			break;
		case 2: // left
			dir.SetXandY(-1, 0);
			break;
		case 3: // right
			dir.SetXandY(1, 0);
			break;
		}
		*GetPosition() += dir;
	}
}

void Goblin::OnDestroyed()
{
	if (GetHealth() <= 0) {
		GameManager::getGM()->RemoveGoblin(this);
	}
}
