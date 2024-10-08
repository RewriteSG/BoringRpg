
#include "Furniture.h"
#include "GameManager.h"
#include "BedSprite.h"
#include "BedroomCabinetSprite.h"
#include "Player.h"
#include "BedroomTableSprite.h"
#include "LivingRoomCabinetSprite.h"
#include "BedroomCabinet2Sprite.h"
#include "TelevisionSprite.h"
#include "LivingroomTableSprite.h"
#include "EmptySofaSprite.h"
#include "DoorSprites.h"
#include "StoreRoomDoorSprite.h"
#include "ToiletDoorSprite.h"
#include "ToiletBowlSprite.h"
#include "ShowerAreaSprite.h"
#include "ToiletCabinetSprite.h"
#include "ClockSprite.h"
#include "SceneManager.h"
#include "BoxSprite.h"
#include "EmptyBoxType1Sprite.h"
#include "EmptyBoxType2Sprite.h"
#include "PlanksSprite.h"
#include "SinkSprite.h"
#include "KitchenTableSprite.h"
#include "KitchenCabinetSprite.h"
#include "StoveSprite.h"
#include "TrashCanSprite.h"
#include "FridgeSprite.h"


Furniture::Furniture(TypeOfFurniture type, Vector2 toPos)
{
	furniture = type;
	*GetPosition() = toPos;
	switch (furniture)
	{
	case Furniture::SofaKey:
		name = "Sofa";
		break;
	case Furniture::Box:
		name = "Box";
		SetSprite(new BoxSprite());
		break;
	case Furniture::Sink:
		name = "Sink";
		SetSprite(new SinkSprite());
		break;
	case Furniture::KitchenTable:
		name = "Kitchen Table";
		SetSprite(new KitchenTableSprite());
		break;
	case Furniture::Planks:
		name = "Shelf";
		SetSprite(new PlanksSprite());
		break;
	case Furniture::EmptyBoxType1:
		SetSprite(new EmptyBoxType1Sprite());
		break;
	case Furniture::EmptyBoxType2:
		SetSprite(new EmptyBoxType2Sprite());
		break;
	case Furniture::ToiletCabinet:
		name = "Cabinet";
		SetSprite(new ToiletCabinetSprite());
		break;
	case Furniture::ToiletBowl:
		name = "Toilet Bowl";
		SetSprite(new ShowerAreaSprite()); 
		break;
	case Furniture::ShowerArea:
		name = "Shower";
		SetSprite(new ToiletBowlSprite());
		break;
	case Furniture::StoreRoomDoor:
		name = "Store Room Door";
		SetSprite(new StoreRoomDoorSprite());
		break;
	case Furniture::ToiletDoor:
		name = "Toilet Door";
		SetSprite(new ToiletDoorSprite());
		break;
		
	case Furniture::BedRoomDoor:
		name = "Bedroom Door";
		SetSprite(new DoorSprites());
		break;
	case Furniture::EmptySofa:
		name = "Sofa";
		SetSprite(new EmptySofaSprite());
		break;
	case Furniture::BedroomCabinet1:
		name = "Cabinet";
		SetSprite(new BedroomCabinetSprite());
		break;
	case Furniture::Closet:
		name = "Closet";
		SetSprite(new ClosetSprite());
		break;
	case Furniture::LivingRoomCabinet:
		name = "Cabinet";
		SetSprite(new LivingRoomCabinetSprite());
		break;
	case Furniture::Television:
		name = "TV";
		SetSprite(new TelevisionSprite());
		break;
	case Furniture::KitchenCabinet:
		name = "Cabinet";
		SetSprite(new KitchenCabinetSprite());
		break;
	case Furniture::CardBoardBox:

		break;
	case Furniture::LivingroomTable:
		name = "Table";
		SetSprite(new LivingroomTableSprite());
		break;
	case Furniture::Bedroomtable:
		name = "Table";
		SetSprite(new BedroomTableSprite());
		break;
	case Furniture::Fridge:
		name = "Fridge";
		SetSprite(new FridgeSprite());
		break;
	case Furniture::Bed:
		name = "Bed";
		SetSprite(new BedSprite());
		break;
	case Furniture::Phone:
		name = "Phone";
		break;
	case Furniture::ToolBox:
		name = "Tool Box";
		break;
	case Furniture::Stove:
		name = "Stove";
		SetSprite(new StoveSprite());
		break;
	case Furniture::TrashCan:
		name = "Trash Can";
		SetSprite(new TrashCanSprite());
		break;
	case Furniture::Clock:
		name = "Clock";
		SetSprite(new ClockSprite());
		break;
	case Furniture::LivingRoomDoor:
		name = "Living Room Door";
		SetSprite(new DoorSprites());
		break;
	case Furniture::KitchenDoor:
		name = "Kitchen Door";
		SetSprite(new StoreRoomDoorSprite());
		break;
	case Furniture::MainDoor:
		name = "Main Door";
		SetSprite(new StoreRoomDoorSprite());
		break;

	default:
		break;
	}
}

Furniture::Furniture(TypeOfFurniture type, Vector2 toPos, std::string toName)
{
	furniture = type;
	*GetPosition() = toPos;
	name = toName;

	switch (furniture)
	{
	case Furniture::SofaKey:
		break;
	case Furniture::Box:
		SetSprite(new BoxSprite());
		break;
	case Furniture::Sink:
		SetSprite(new SinkSprite());
		break;
	case Furniture::KitchenTable:
		SetSprite(new KitchenTableSprite());
		break;
	case Furniture::Planks:
		SetSprite(new PlanksSprite());
		break;
	case Furniture::EmptyBoxType1:
		SetSprite(new EmptyBoxType1Sprite());
		break;
	case Furniture::EmptyBoxType2:
		SetSprite(new EmptyBoxType2Sprite());
		break;
	case Furniture::ToiletCabinet:
		SetSprite(new ToiletCabinetSprite());
		break;
	case Furniture::ToiletBowl:
		SetSprite(new ToiletBowlSprite());
		break;
	case Furniture::ShowerArea:
		SetSprite(new ShowerAreaSprite());
		break;
	case Furniture::StoreRoomDoor:
		SetSprite(new StoreRoomDoorSprite());
		break;
	case Furniture::ToiletDoor:
		SetSprite(new ToiletDoorSprite());
		break;

	case Furniture::BedRoomDoor:
		SetSprite(new DoorSprites());
		break;
	case Furniture::EmptySofa:
		SetSprite(new EmptySofaSprite());
		break;
	case Furniture::BedroomCabinet1:
		SetSprite(new BedroomCabinetSprite());
		break;
	case Furniture::Closet:
		SetSprite(new ClosetSprite());
		break;
	case Furniture::LivingRoomCabinet:
		SetSprite(new LivingRoomCabinetSprite());
		break;
	case Furniture::Television:
		SetSprite(new TelevisionSprite());
		break;
	case Furniture::KitchenCabinet:
		SetSprite(new KitchenCabinetSprite());
		break;
	case Furniture::CardBoardBox:
		break;
	case Furniture::LivingroomTable:
		SetSprite(new LivingroomTableSprite());
		break;
	case Furniture::Bedroomtable:
		SetSprite(new BedroomTableSprite());
		break;
	case Furniture::Fridge:
		SetSprite(new FridgeSprite());
		break;
	case Furniture::Bed:
		SetSprite(new BedSprite());
		break;
	case Furniture::Phone:
		break;
	case Furniture::ToolBox:
		break;
	case Furniture::Stove:
		SetSprite(new StoveSprite());
		break;
	case Furniture::TrashCan:
		SetSprite(new TrashCanSprite());
		break;
	case Furniture::Clock:
		SetSprite(new ClockSprite());
		break;
	case Furniture::LivingRoomDoor:
		SetSprite(new DoorSprites());
		break;
	case Furniture::KitchenDoor:
		SetSprite(new StoreRoomDoorSprite());
		break;

	default:
		break;
	}
}

Furniture::Furniture(TypeOfFurniture type, Vector2 toPos, bool isInvisible)
{
	furniture = type;
	*GetPosition() = toPos;
	SetRenderSprite(false);
	switch (furniture)
	{
	case Furniture::SofaKey:
		name = "Sofa";
		break;
	case Furniture::Box:
		name = "Box";
		//SetSprite(new BoxSprite());
		break;
	case Furniture::Sink:
		name = "Sink";
		//SetSprite(new SinkSprite());
		break;
	case Furniture::KitchenTable:
		name = "Kitchen Table";
		//SetSprite(new KitchenTableSprite());
		break;
	case Furniture::Planks:
		name = "Shelf";
		//SetSprite(new PlanksSprite());
		break;
	case Furniture::EmptyBoxType1:
		//SetSprite(new EmptyBoxType1Sprite());
		break;
	case Furniture::EmptyBoxType2:
		//SetSprite(new EmptyBoxType2Sprite());
		break;
	case Furniture::ToiletCabinet:
		name = "Toilet Cabinet";
		//SetSprite(new ToiletCabinetSprite());
		break;
	case Furniture::ToiletBowl:
		name = "Toilet Bowl";
		//SetSprite(new ToiletBowlSprite());
		break;
	case Furniture::ShowerArea:
		name = "Shower";
		//SetSprite(new ShowerAreaSprite());
		break;
	case Furniture::StoreRoomDoor:
		name = "Store Room Door";
		//SetSprite(new StoreRoomDoorSprite());
		break;
	case Furniture::ToiletDoor:
		name = "Toilet Door";
		//SetSprite(new ToiletDoorSprite());
		break;

	case Furniture::BedRoomDoor:
		name = "Bedroom Door";
		//SetSprite(new DoorSprites());
		break;
	case Furniture::EmptySofa:
		name = "Sofa";
		//SetSprite(new EmptySofaSprite());
		break;
	case Furniture::BedroomCabinet1:
		name = "Cabinet";
		//SetSprite(new BedroomCabinetSprite());
		break;
	case Furniture::Closet:
		name = "Closet";
		//SetSprite(new BedroomCabinet2Sprite());
		break;
	case Furniture::LivingRoomCabinet:
		name = "Cabinet";
		//SetSprite(new LivingRoomCabinetSprite());
		break;
	case Furniture::Television:
		name = "TV";
		//SetSprite(new TelevisionSprite());
		break;
	case Furniture::KitchenCabinet:
		name = "Cabinet";
		//SetSprite(new KitchenCabinetSprite());
		break;
	case Furniture::CardBoardBox:

		break;
	case Furniture::LivingroomTable:
		name = "Table";
		//SetSprite(new LivingroomTableSprite());
		break;
	case Furniture::Bedroomtable:
		name = "Table";
		//SetSprite(new BedroomTableSprite());
		break;
	case Furniture::Fridge:
		name = "Fridge";
		//SetSprite(new FridgeSprite());
		break;
	case Furniture::Bed:
		name = "Bed";
		//SetSprite(new BedSprite());
		break;
	case Furniture::Phone:
		name = "Phone";
		break;
	case Furniture::ToolBox:
		name = "Tool Box";
		break;
	case Furniture::Stove:
		name = "Stove";
		//SetSprite(new StoveSprite());
		break;
	case Furniture::TrashCan:
		name = "Trash Can";
		//SetSprite(new TrashCanSprite());
		break;
	case Furniture::Clock:
		name = "Clock";
		//SetSprite(new ClockSprite());
		break;
	case Furniture::LivingRoomDoor:
		name = "Living Room Door";
		//SetSprite(new DoorSprites());
		break;
	case Furniture::KitchenDoor:
		name = "Kitchen Door";
		//SetSprite(new StoreRoomDoorSprite());
		break;

	default:
		break;
	}
}

void Furniture::Start()
{
}

void Furniture::Collided(GameObject* obj)
{
	return;
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
	case Furniture::BedroomCabinet1:
		GameManager::getGM()->InteractionsMgr.BedRoomDrawerInteracted(this, obj);
		break;
	case Furniture::Closet:

		GameManager::getGM()->InteractionsMgr.ClosetDoorInteracted(this, obj);
		break;
	case Furniture::LivingRoomCabinet:
		GameManager::getGM()->InteractionsMgr.LivingRoomCabinetInteracted(this, obj);
		break;
	case Furniture::Television:
		GameManager::getGM()->InteractionsMgr.TelevisionInteracted(this, obj);
		break;
	case Furniture::KitchenCabinet:
		GameManager::getGM()->InteractionsMgr.KitchenCabinetInteracted(this, obj);
		break;
	case Furniture::Sink:
		GameManager::getGM()->InteractionsMgr.ShowerInteracted(this, obj);
		break;
	case Furniture::Planks:
		GameManager::getGM()->InteractionsMgr.PlanksInteracted(this, obj);
		break;
	case Furniture::EmptyBoxType1:
	case Furniture::EmptyBoxType2:
		GameManager::getGM()->InteractionsMgr.BoxInteracted(this, obj, GetID());
		break;
	case Furniture::LivingroomTable:
		GameManager::getGM()->InteractionsMgr.TableInteracted(this, obj);
		break;
	case Furniture::Phone:
		break;
	case Furniture::Box:
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
	case Furniture::Clock:
		GameManager::getGM()->InteractionsMgr.ClockInteracted(this, obj);
		break;
	case Furniture::BedRoomDoor:
	GameManager::getGM()->InteractionsMgr.BedroomDoorInteracted(this, obj);
		break;
	case Furniture::ToiletBowl:
		GameManager::getGM()->InteractionsMgr.ToiletBowlInteracted(this, obj);
		break;
	case Furniture::ShowerArea:
		GameManager::getGM()->InteractionsMgr.ShowerInteracted(this, obj);
		break;
	case Furniture::ToiletCabinet:
		GameManager::getGM()->InteractionsMgr.ToiletCabinetInteracted(this, obj);
		break;
	case Furniture::ToiletDoor:
		GameManager::getGM()->InteractionsMgr.ToiletDoorInteracted(this, obj);
		break;
	case Furniture::StoreRoomDoor:
		GameManager::getGM()->InteractionsMgr.StoreRoomDoorInteracted(this, obj);
		break;
	case Furniture::LivingRoomDoor:
		GameManager::getGM()->InteractionsMgr.LivingRoomDoorInteracted(this, obj);
		break;
	case Furniture::Bedroomtable:
		GameManager::getGM()->InteractionsMgr.BedroomTableInteracted(this, obj);
		break;
	}

}
void Furniture::InteractFurniture(GameObject* obj)
{
	Player* plr = dynamic_cast<Player*>(obj);
	GameManager::getGM()->ClearDialogue();
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
	case Furniture::BedroomCabinet1:
		GameManager::getGM()->InteractionsMgr.BedRoomDrawerInteracted(this, obj);
		break;
	case Furniture::Closet:

		GameManager::getGM()->InteractionsMgr.ClosetDoorInteracted(this, obj);
		break;
	case Furniture::LivingRoomCabinet:
		GameManager::getGM()->InteractionsMgr.LivingRoomCabinetInteracted(this, obj);
		break;
	case Furniture::Television:
		GameManager::getGM()->InteractionsMgr.TelevisionInteracted(this, obj);
		break;

	case Furniture::KitchenCabinet:
		GameManager::getGM()->InteractionsMgr.KitchenCabinetInteracted(this, obj);
		break;
	case Furniture::Sink:
		GameManager::getGM()->InteractionsMgr.SinkInteracted(this, obj, true);
		break;
	case Furniture::Planks:
		GameManager::getGM()->InteractionsMgr.PlanksInteracted(this, obj);
		break;
	case Furniture::EmptyBoxType1:
	case Furniture::EmptyBoxType2:
		GameManager::getGM()->InteractionsMgr.BoxInteracted(this, obj, GetID());
		break;
	case Furniture::LivingroomTable:
		GameManager::getGM()->InteractionsMgr.TableInteracted(this, obj);
		break;
	case Furniture::Phone:
		break;
	case Furniture::Box:
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
	case Furniture::Clock:
		GameManager::getGM()->InteractionsMgr.ClockInteracted(this, obj);
		break;
	case Furniture::BedRoomDoor:
		GameManager::getGM()->InteractionsMgr.BedroomDoorInteracted(this, obj);
		break;
	case Furniture::ToiletBowl:
		GameManager::getGM()->InteractionsMgr.ToiletBowlInteracted(this, obj);

		break;
	case Furniture::ShowerArea:
		GameManager::getGM()->InteractionsMgr.ShowerInteracted(this, obj);
		break;
	case Furniture::ToiletCabinet:
		GameManager::getGM()->InteractionsMgr.ToiletCabinetInteracted(this, obj);
		break;
	case Furniture::ToiletDoor:
		GameManager::getGM()->InteractionsMgr.ToiletDoorInteracted(this, obj);
		break;
	case Furniture::StoreRoomDoor:
		GameManager::getGM()->InteractionsMgr.StoreRoomDoorInteracted(this, obj);
		break;
	case Furniture::LivingRoomDoor:
		GameManager::getGM()->InteractionsMgr.LivingRoomDoorInteracted(this, obj);
		break;
	case Furniture::Bedroomtable:

		GameManager::getGM()->InteractionsMgr.BedroomTableInteracted(this, obj);
		break;
	case Furniture::KitchenDoor:
		GameManager::getGM()->InteractionsMgr.KitchenDoorInteracted(this, obj);
		break;
	case Furniture::MainDoor:
		GameManager::getGM()->InteractionsMgr.MainDoorInteracted(this, obj);
		break;
	case Furniture::Fridge:
		GameManager::getGM()->InteractionsMgr.FridgeInteracted(this, obj);
		break;
	case Furniture::KitchenTable:
		GameManager::getGM()->InteractionsMgr.KitchenTableInteracted(this, obj);
		break;
	default:
		break;
	}
}


	



Furniture::TypeOfFurniture Furniture::GetFurnitureType()
{
	return furniture;
}