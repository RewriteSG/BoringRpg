#pragma once
#include "GameObject.h"
class InteractionsManager
{
public:
	bool hasSofaKeyCollected;
	bool hasClosetDoorOpened;
	bool hasCalledTheCops;
	bool hasHammer;
	bool hasNails;
	bool hasPlanks;
	bool hasShampoo;
	bool hasKnife;
	bool hasDuctTape;
	bool hasMetalPan;


	InteractionsManager();

	/// Furnitures
	void SofaInteracted(GameObject* sofa, GameObject* player);
	void SofaInteracted(GameObject* sofa, GameObject* player, bool isNothing);
	void SinkInteracted(GameObject* sink, GameObject* player);
	void SinkInteracted(GameObject* sink, GameObject* player, bool isNothing);
	void PlanksInteracted(GameObject* planks, GameObject* player);
	void ToolboxInteracted(GameObject* box, GameObject* player);
	void BoxInteracted(GameObject* box, GameObject* player, int random);
	void StoveInteracted(GameObject* stove, GameObject* player);
	void KitchenCabinetInteracted(GameObject* kitchenCabinet, GameObject* player);
	void TrashCanInteracted(GameObject* trashCan, GameObject* player, int random);
	void TableInteracted(GameObject* table, GameObject* player);
	void PhoneInteracted(GameObject* phone, GameObject* player);
	void LivingRoomCabinetInteracted(GameObject* livingRoomCabinet, GameObject* player);
	void BedRoomCabinetInteracted(GameObject* bedRoomCabinet, GameObject* player);
	void BedInteracted(GameObject* bed, GameObject* player);
	void TelevisionInteracted(GameObject* bed, GameObject* player);

	/// Doors
	void MainDoorInteracted(GameObject* MainDoor, GameObject* player);
	void BedroomDoorInteracted(GameObject* BedroomDoor, GameObject* player);
	void ClosetDoorInteracted(GameObject* closetDoor, GameObject* player);
	void KitchenDoorInteracted(GameObject* KitchenDoor, GameObject* player);
	void BathroomDoorInteracted(GameObject* BathroomDoor, GameObject* player);
};

