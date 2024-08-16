#include "Door.h"
#include "GameManager.h"
#include "Player.h"
Door::Door(TypeOfDoor type, Vector2 toPos)
{
	door = type;
	*GetPosition() = toPos;
}

void Door::Collided(GameObject* obj)
{
	Player* plr = dynamic_cast<Player*>(obj);
	if (!plr)
		return;
	switch (door)
	{
	case Door::ClosetDoor:
		GameManager::getGM()->InteractionsMgr.ClosetDoorInteracted(this, obj);
		break;
	case Door::BathroomDoor:
		GameManager::getGM()->InteractionsMgr.ToiletDoorInteracted(this, obj);
		break;
	case Door::MainDoor:
		GameManager::getGM()->InteractionsMgr.MainDoorInteracted(this, obj);
		break;
	case Door::KitchenDoor:
		GameManager::getGM()->InteractionsMgr.KitchenDoorInteracted(this, obj);
		break;
	case Door::BedroomDoor:		
		GameManager::getGM()->InteractionsMgr.BedroomDoorInteracted(this, obj);
		break;
	default:
		break;
	}

	Robber* rob = dynamic_cast<Robber*>(obj);
	if (!rob)
		return;
	switch (door)
	{
	case Door::ClosetDoor:
		GameManager::getGM()->InteractionsMgr.ClosetDoorInteracted(this, obj);
		break;
	case Door::BathroomDoor:
		GameManager::getGM()->InteractionsMgr.BathroomDoorInteracted(this, obj);
		break;
	case Door::MainDoor:
		GameManager::getGM()->InteractionsMgr.MainDoorInteracted(this, obj);
		break;
	case Door::KitchenDoor:
		GameManager::getGM()->InteractionsMgr.KitchenDoorInteracted(this, obj);
		break;
	case Door::BedroomDoor:
		GameManager::getGM()->InteractionsMgr.BedroomDoorInteracted(this, obj);
		break;
	default:
		break;
	}
}


