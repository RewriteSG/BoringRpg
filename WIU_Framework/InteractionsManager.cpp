#include "InteractionsManager.h"
#include "GameManager.h"
#include "ObjectManager.h"
#include "Furniture.h"

InteractionsManager::InteractionsManager()
{

}

void InteractionsManager::SofaInteracted(GameObject* sofa, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(-2, 14), false);
	if (hasSofaKeyCollected) 
	{
		ui->PrintDialogue(Vector2(-2, 14), "You: I don't think there is anything else I can do here.");
	}
	else 
	{
		ui->PrintDialogue(Vector2(-2, 14), "You: I hid my CABINET KEY under the sofa so no one can find it.");
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		int choosenItem = ui->PickDialogue(Vector2(-2, 14), "Pick up the key?");
		switch (choosenItem)
		{
		case 0:
			timer.increaseTimeTaken(5);
			hasSofaKeyCollected = true;
			GameManager::getGM()->inventory.PickupItem("Cabinet Key");
			ui->PrintDialogue(Vector2(-2, 14), "Picked up CABINET KEY!");
			break;
		case 1:
			break;
		}
	}
}

void InteractionsManager::SofaInteracted(GameObject* sofa, GameObject* player, bool isNothing)
{
}

void InteractionsManager::SinkInteracted(GameObject* sink, GameObject* player)
{
	timer.increaseTimeTaken(5);
}

void InteractionsManager::SinkInteracted(GameObject* sink, GameObject* player, bool isNothing)
{
}

void InteractionsManager::PlanksInteracted(GameObject* planks, GameObject* player)
{
	timer.increaseTimeTaken(5);
}

void InteractionsManager::ToolboxInteracted(GameObject* box, GameObject* player)
{
	timer.increaseTimeTaken(5);
}

void InteractionsManager::BoxInteracted(GameObject* box, GameObject* player, int random)
{
	timer.increaseTimeTaken(5);
}

void InteractionsManager::StoveInteracted(GameObject* stove, GameObject* player)
{
	timer.increaseTimeTaken(5);
}

void InteractionsManager::KitchenCabinetInteracted(GameObject* kitchenCabinet, GameObject* player)
{
	timer.increaseTimeTaken(5);
}

void InteractionsManager::TrashCanInteracted(GameObject* trashCan, GameObject* player, int random)
{
	timer.increaseTimeTaken(5);
}

void InteractionsManager::TableInteracted(GameObject* table, GameObject* player)
{
	timer.increaseTimeTaken(5);
}

void InteractionsManager::PhoneInteracted(GameObject* phone, GameObject* player)
{
	timer.increaseTimeTaken(5);
}

void InteractionsManager::LivingRoomCabinetInteracted(GameObject* livingRoomCabinet, GameObject* player)
{
	timer.increaseTimeTaken(5);
}

void InteractionsManager::BedRoomCabinetInteracted(GameObject* bedRoomCabinet, GameObject* player)
{
	timer.increaseTimeTaken(5);
}

void InteractionsManager::BedInteracted(GameObject* bed, GameObject* player)
{
	timer.increaseTimeTaken(5);
}

void InteractionsManager::TelevisionInteracted(GameObject* bed, GameObject* player)
{
	timer.increaseTimeTaken(5);
}

void InteractionsManager::MainDoorInteracted(GameObject* MainDoor, GameObject* player)
{
	timer.increaseTimeTaken(5);
}

void InteractionsManager::BedroomDoorInteracted(GameObject* BedroomDoor, GameObject* player)
{
	timer.increaseTimeTaken(5);
}

void InteractionsManager::ClosetDoorInteracted(GameObject* closetDoor, GameObject* player)
{
	timer.increaseTimeTaken(5);
}

void InteractionsManager::KitchenDoorInteracted(GameObject* KitchenDoor, GameObject* player)
{
	timer.increaseTimeTaken(5);
}

void InteractionsManager::BathroomDoorInteracted(GameObject* BathroomDoor, GameObject* player)
{
	timer.increaseTimeTaken(5);
}

void InteractionsManager::ToiletCabinetInteracted(GameObject* toiletCabinet, GameObject* player)
{

}

void InteractionsManager::Start()
{
	ui = GameManager::getGM()->gameUI;
}
