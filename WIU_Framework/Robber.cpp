#include "Robber.h"
#include "RobberSprite.h"
#include <iostream>
Robber::Robber()
{
	Start();
}
Robber::Robber(Vector2 toPos)
{
	Start();
	*GetPosition() = toPos;
}
void Robber::Start()
{
	SetSprite(new RobberSprite()); 
}
void Robber::Update()
{

	
	/*switch (steps)
	{
	case 0:
	
		*GetPosition() = Vector2(7, 7);
		break;
	case 1:		
		*GetPosition() = Vector2(7, 8);

		break;
	case 2:
		*GetPosition() = Vector2(1, 3);
		break;
	case 3:
		*GetPosition() = Vector2(0, 2);
		break;
	case 4:
		*GetPosition() = Vector2(4, 3);
		break;
	case 5:
		*GetPosition() = Vector2(5, 2);
		break;
	case 6:
		*GetPosition() = Vector2(6, 6);
		break;
	case 7:
		*GetPosition() = Vector2(1, 8);
		break;
	}
	steps++;*/
}
void Robber::Collided(GameObject* collision)
{
	//HealingGlobe* healGlobe = dynamic_cast<HealingGlobe*>(collision);
	//if (healGlobe) 
	//{
	//	ObjectManager::getObjectManager()->DestroyObject(collision);
	//	SetHealth(GetHealth() + healGlobe->GetHeal());
	//	*GetPosition() = *collision->GetPosition();
	//}
	//Weapon* wpn = dynamic_cast<Weapon*>(collision);
	//if (wpn)
	//{
	//	collision->SetActive(false);
	//	SetAttackDamage(GetAttackDamage() + wpn->GetDamageIncrease());
	//	SetWeaponHeld(wpn);
	//	*GetPosition() = *collision->GetPosition();
	//}
}

void Robber::OnDestroyed()
{

}
