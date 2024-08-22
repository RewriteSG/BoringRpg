#pragma once
#include "GameObject.h"
#include "TimeSystem.h"
#include "UI.h"

class InteractionsManager
{
	void SeperateInput(std::string input, std::string& input1, std::string& input2);
public:
	//timer
	TimeSystem* timeSystem;
	std::string soapLocation;
	Vector2 soapPosition; 

	UI* ui;
	bool isNailSetup;
	bool isPlankSetup;
	bool isPlayerHidden;
	bool isSoapSetup;
	bool isBarricadeSetup;
	bool isPlayerSleeping;
	bool isStoreRoomUnlocked;
	bool isClosetUnlocked;
	bool isPlayerSucide;
	bool isCurtainOpen;
	bool isHidInCloset;

	bool hasFoundKeyUnderSofa;
	bool hasCabinetKeyCollected;
	bool hasStoreRoomKeyCollected;
	bool hasClosetKeyCollected;
	bool hasCalledTheCops;
	bool hasHammer;
	bool hasNails;
	bool hasPlanks;
	bool hasSoap;
	bool hasKnife;
	bool hasDuctTape;
	bool hasMetalPan;
	bool isDoorBarricaded;
	//bool isfirstCheckClock;
	static bool hasSearchedForSoap;
	static bool LastTimeChecked;
	static bool hasKnownKey;
	int trashCanInteractions = 0;
	InteractionsManager();

	/// Furnitures
	void SofaInteracted(GameObject* sofa, GameObject* player);
	void SofaInteracted(GameObject* sofa, GameObject* player, bool isNothing);
	void ShowerInteracted(GameObject* sink, GameObject* player);
	void SinkInteracted(GameObject* sink, GameObject* player, bool isNothing);
	void PlanksInteracted(GameObject* planks, GameObject* player);
	void ToolboxInteracted(GameObject* box, GameObject* player);
	void BoxInteracted(GameObject* box, GameObject* player, int random);
	void StoveInteracted(GameObject* stove, GameObject* player);
	void KitchenCabinetInteracted(GameObject* kitchenCabinet, GameObject* player);
	void TrashCanInteracted(GameObject* trashCan, GameObject* player, int random);
	void TableInteracted(GameObject* table, GameObject* player);
	void BedroomTableInteracted(GameObject* phone, GameObject* player);
	void LivingRoomCabinetInteracted(GameObject* livingRoomCabinet, GameObject* player);
	void BedRoomDrawerInteracted(GameObject* bedRoomCabinet, GameObject* player);
	void BedInteracted(GameObject* bed, GameObject* player);
	void TelevisionInteracted(GameObject* bed, GameObject* player);
	void ToiletCabinetInteracted(GameObject* toiletCabinet, GameObject* player);
	/// Doors
	void MainDoorInteracted(GameObject* MainDoor, GameObject* player);
	void BedroomDoorInteracted(GameObject* BedroomDoor, GameObject* player);
	void ClosetDoorInteracted(GameObject* closetDoor, GameObject* player);
	void KitchenDoorInteracted(GameObject* KitchenDoor, GameObject* player);
	void ToiletDoorInteracted(GameObject* BathroomDoor, GameObject* player);
	void ToiletBowlInteracted(GameObject* ToiletBowl, GameObject* player);
	void LivingRoomDoorInteracted(GameObject* BathroomDoor, GameObject* player);
	void StoreRoomDoorInteracted(GameObject* storeRoomDoor, GameObject* player);
	void ClockInteracted(GameObject* clock, GameObject* player);
	bool UseItem(std::string useItem, GameObject* player);
	//void BarricadeDoor(GameObject* door, GameObject* player);
	void FridgeInteracted(GameObject* fridge, GameObject* player);
	void KitchenTableInteracted(GameObject* table, GameObject* player);
	void Start();
	void Start(bool isGameStarted);
	


	// --------------- Interactions Images ---------------
	void MainDoorImage();
	void DoorOpeningImage();
	void SofaImage();
	void SofaKeyUnderImage();
	void SofaKeyUnderImage(bool);
	void TableImage();
	void SinkImage();
	void PlanksImage();
	void PlanksImage(bool);
	void ToolboxImage();
	void ToolboxImage(bool);
	void StoveImage();
	void StoveImage(bool);
	void KitchenCabinetImage();
	void KitchenCabinetImage(bool);
	void TrashCanImage();
	void BedroomTableImage();
	void LivingRoomCabinetImage();
	void LivingRoomCabinetImage(bool);
	void BedRoomDrawerImage();
	void BedRoomDrawerImage(bool);
	void BedImage();
	void TelevisionImage();
	void TelevisionImage(bool);
	void TelevisionOtherChannelImage();
	void ToiletCabinetImage();
	void ToiletCabinetImage(bool);
	void BedroomDoorImage();
	void ClosetDoorImage();
	void ClosetDoorImage(bool);
	void KitchenDoorImage();
	void ToiletDoorImage();
	void ToiletBowlImage();
	void LivingRoomDoorImage();
	void StoreRoomDoorImage();
	void KeyImage();
	void ClockImage();
	void KitchenTableImage();
	void BarricadeDoorImage();
	void KnifeImage();
	void HammerAndNailsImage();
	void PlanksItemImage(); 
	void SoapImage();
	void DuctTapeImage();
	void MetalPanImage();
	void EmptyBoxImage();
	void FridgeImage();
	void FridgeImage(bool);
	void ShowerCurtainImage();
	void ShowerImage();
	void ShowerImage(bool);
	void ShowerNoShampooImage();
	void PouringShampooImage();

};

