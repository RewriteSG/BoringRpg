#include "Player.h"
#include <iostream>
#include "ObjectManager.h"
#include "Application.h"
#include "GameManager.h"
#include "PlayerSprite.h"

Player* Player::playerInstance = nullptr;

Player::Player()
{
	Start();
	name = "Hazwan";
	playerInstance = this;
}
void Player::Start()
{
	SetSprite(new PlayerSprite());
}
void Player::Update()
{
}
void Player::Collided(GameObject* collision)
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

void Player::OnDestroyed()
{

}
