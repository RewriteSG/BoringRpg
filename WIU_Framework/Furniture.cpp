#include "Furniture.h"
#include "GameManager.h"
#include "Player.h"
Furniture::Furniture(TypeOfFurniture type, Vector2 toPos)
{
	furniture = type;
	*GetPosition() = toPos;
}

void Furniture::Start()
{
}

void Furniture::Collided(GameObject* obj)
{
	Player* plr = dynamic_cast<Player*>(obj);
	if (!plr)
		return;
	switch (furniture)
	{
	case Furniture::SofaKey:
		GameManager::getGM()->InteractionsMgr.SofaInteracted(this, obj);
		break;
	case Furniture::EmptySofa:
		GameManager::getGM()->InteractionsMgr.SofaInteracted(this, obj, true);
		break;
	case Furniture::BedroomCabinet:
		GameManager::getGM()->InteractionsMgr.BedRoomCabinetInteracted(this, obj);
		break;
	case Furniture::LivingRoomCabinet:
		GameManager::getGM()->InteractionsMgr.LivingRoomCabinetInteracted(this, obj);
		break;
	case Furniture::TelevisionCabinet:
		GameManager::getGM()->InteractionsMgr.TelevisionInteracted(this, obj);
		break;
	case Furniture::KitchenCabinet:
		GameManager::getGM()->InteractionsMgr.KitchenCabinetInteracted(this, obj);
		break;
	case Furniture::Sink:
		GameManager::getGM()->InteractionsMgr.SinkInteracted(this, obj);
		break;
	case Furniture::Planks:
		GameManager::getGM()->InteractionsMgr.PlanksInteracted(this, obj);
		break;
	case Furniture::CardBoardBox:
		GameManager::getGM()->InteractionsMgr.BoxInteracted(this, obj, GetID());
		break;
	case Furniture::Table:
		GameManager::getGM()->InteractionsMgr.TableInteracted(this, obj);
		break;
	case Furniture::Phone:
		GameManager::getGM()->InteractionsMgr.PhoneInteracted(this, obj);
		break;
	case Furniture::ToolBox:
		GameManager::getGM()->InteractionsMgr.ToolboxInteracted(this, obj);
		break;
	case Furniture::Stove:
		GameManager::getGM()->InteractionsMgr.StoveInteracted(this, obj);
		break;
	case Furniture::Bed:
		GameManager::getGM()->InteractionsMgr.BedInteracted(this, obj);
		break;
	case Furniture::TrashCan:
		GameManager::getGM()->InteractionsMgr.TrashCanInteracted(this, obj, 0);
		break;
	default:
		break;
	}
}
