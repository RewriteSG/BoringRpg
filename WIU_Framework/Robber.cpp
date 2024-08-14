#include "Robber.h"
#include "RobberSprite.h"
#include <chrono>
#include <thread>
#include <iostream>
Robber::Robber()
{
	Start();
}
Robber::Robber(Vector2 toPos)
{
	Start();
	*GetPosition() = toPos;
	//GetPosition() = toPos;
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
//Vector2 Robber::GetPosition() const
//{
//	return position;
//	//return Vector2();
//}


//in update?
//only add time if robber moves

//Vector2 Robber::GetPosition() const
//{
//	return Vector2();
//}
//

