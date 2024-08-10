#include "Player.h"
#include <iostream>
#include "HealingGlobe.h"
#include "ObjectManager.h"
#include "Application.h"
#include "Goblin.h"
Player::Player()
{
}
void Player::Start()
{
}
void Player::Update()
{

}
void Player::Collided(GameObject* collision)
{
	HealingGlobe* healGlobe = dynamic_cast<HealingGlobe*>(collision);
	if (healGlobe) 
	{
		ObjectManager::getObjectManager()->DestroyObject(collision);
		SetHealth(GetHealth() + healGlobe->GetHeal());
		*GetPosition() = *collision->GetPosition();
	}
	Weapon* wpn = dynamic_cast<Weapon*>(collision);
	if (wpn)
	{
		collision->SetActive(false);
		SetAttackDamage(GetAttackDamage() + wpn->GetDamageIncrease());
		SetWeaponHeld(wpn);
		*GetPosition() = *collision->GetPosition();
	}
}

void Player::OnDestroyed()
{
	if (GetHealth() <= 0) {
		GameManager::getGM()->SetPlayer(nullptr);
	}
}
