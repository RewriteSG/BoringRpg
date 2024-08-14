#pragma once
#include "Items.h"
class Furniture :
    public Item
{
public:
	enum TypeOfFurniture
	{
		SofaKey,
		Clock,
		EmptySofa,
		BedroomCabinet1,
		BedroomCabinet2,
		LivingRoomCabinet,
		Television,
		KitchenCabinet,
		Sink,
		Planks,
		CardBoardBox,
		LivingroomTable,
		Bedroomtable,
		Phone,
		ToolBox,
		Stove,
		Bed,
		TrashCan
	};

	///// Furnitures
	//void SofaInteracted(GameObject* sofa, GameObject* player);
	//void SinkInteracted(GameObject* sink, GameObject* player);
	//void PlanksInteracted(GameObject* planks, GameObject* player);
	//void ToolboxInteracted(GameObject* box, GameObject* player);
	//void BoxInteracted(GameObject* box, GameObject* player, int random);
	//void StoveInteracted(GameObject* stove, GameObject* player);
	//void KitchenCabinetInteracted(GameObject* kitchenCabinet, GameObject* player);
	//void TrashCanInteracted(GameObject* trashCan, GameObject* player, int random);
	//void TableInteracted(GameObject* table, GameObject* player);
	//void PhoneInteracted(GameObject* phone, GameObject* player);
	//void LivingRoomCabinetInteracted(GameObject* livingRoomCabinet, GameObject* player);
	//void BedRoomCabinetInteracted(GameObject* bedRoomCabinet, GameObject* player);
	//void BedInteracted(GameObject* bed, GameObject* player);
	//void TelevisionInteracted(GameObject* bed, GameObject* player);
	//void MainDoorInteracted(GameObject* MainDoor, GameObject* player);
	//void BedroomDoorInteracted(GameObject* BedroomDoor, GameObject* player);
	//void ClosetDoorInteracted(GameObject* closetDoor, GameObject* player);
	//void KitchenDoorInteracted(GameObject* KitchenDoor, GameObject* player);
	//void BathroomDoorInteracted(GameObject* BathroomDoor, GameObject* player);
	TypeOfFurniture furniture;
	Furniture(TypeOfFurniture type, Vector2 toPos);
	Furniture(TypeOfFurniture type, Vector2 toPos, bool isInvisible);
	void Start();
	void Collided(GameObject* obj) override;

};

