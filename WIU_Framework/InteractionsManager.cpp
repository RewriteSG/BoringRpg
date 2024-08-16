#include "InteractionsManager.h"
#include "GameManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "Furniture.h"

InteractionsManager::InteractionsManager()
{
	timeSystem = &GameManager::getGM()->TimeSys;
}

void InteractionsManager::SofaInteracted(GameObject* sofa, GameObject* player)
{
	/*Start();
	ui->CreateOptionUI(Vector2(-2, 14), false);
	if (hasStoreRoomKeyCollected) 
	{
		ui->PrintDialogue(Vector2(-2, 14), "You: I don't think there is anything else I can do here.");
	}
	else 
	{
		ui->PrintDialogue(Vector2(-2, 14), "You: I remember hiding my STOREROOM KEY under the sofa so no one can find it.");
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		int choosenItem = ui->PickDialogue(Vector2(-2, 14), "Take the key?");
		switch (choosenItem)
		{
		case 0:
			timer.increaseTimeTaken(5);
			hasStoreRoomKeyCollected = true;
			GameManager::getGM()->inventory.PickupItem("StoreRoom Key");
			ui->PrintDialogue(Vector2(-2, 14), "Picked up STOREROOM KEY!");
			break;
		case 1:
			break;
		}
	}*/
	Start();
	ui->CreateOptionUI(Vector2(-2, 14), false);
	int choosenItem;
	switch (trashCanInteractions)
	{
	case 0:
		ui->PrintDialogue(Vector2(-2, 14), "A trash can, not remarkable in any way.");
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		choosenItem = ui->PickDialogue(Vector2(-2, 14), "Search the trash can?");
		switch (choosenItem)
		{
		case 0:
			timeSystem->increaseTimeTaken(5);
			ui->PrintDialogue(Vector2(-2, 14), "You searched the trash can and found nothing.");

			break;
		case 1:
			break;
		}
		break;
	case 1:
		ui->PrintDialogue(Vector2(-2, 14), "You've been staring at it for a while, but it's just an ordinary trash can.");
		ui->PrintDialogue(Vector2(-2, 14), "You: Maybe try again?");
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		choosenItem = ui->PickDialogue(Vector2(-2, 14), "Search the trash can?");
		switch (choosenItem)
		{
		case 0:
			timeSystem->increaseTimeTaken(5);
			ui->PrintDialogue(Vector2(-2, 14), "You searched the trash can and found nothing.");

			break;
		case 1:
			break;
		}
		break;
	case 2:
		ui->PrintDialogue(Vector2(-2, 14), "You try to hold back the urge to open it.");
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		choosenItem = ui->PickDialogue(Vector2(-2, 14), "Search the trash can?");
		switch (choosenItem)
		{
		case 0:
			ui->PrintDialogue(Vector2(-2, 14), "As you continue staring at the trash cans, they seem to turn before your very eyes.");
			ui->PrintDialogue(Vector2(-2, 14), "The edges are no longer rusty, and the dents are smoothed over.");
			ui->PrintDialogue(Vector2(-2, 14), "From under the lid comes a faint golden glow, sweet and alluring.");
			ui->PrintDialogue(Vector2(-2, 14), "For a moment, the trash cans turn into treasure chests...And it's happening again.");
			ui->PrintDialogue(Vector2(-2, 14), "You take a depth breath and open the lid.");
			ui->PrintDialogue(Vector2(-2, 14), "It's empty...");
			ui->PrintDialogue(Vector2(-2, 14), "Wait!");
			ui->PrintDialogue(Vector2(-2, 14), "You reach deeper into the trash can.");
			ui->PrintDialogue(Vector2(-2, 14), "There is still nothing.");
			ui->PrintDialogue(Vector2(-2, 14), "You pry deeper, hoping to find something valuable.");
			ui->PrintDialogue(Vector2(-2, 14), "Time passed, and you didn't notice someone opening the front door and walk behind you.");
			ui->PrintDialogue(Vector2(-2, 14), "???: Just what are you doing?");
			ui->PrintDialogue(Vector2(-2, 14), "You: Who's- ");
			ui->PrintDialogue(Vector2(-2, 14), "Before you could turn around, the mysterious man snaps your neck");
			ui->PrintDialogue(Vector2(-2, 14), "You died.");
			ui->PrintDialogue(Vector2(-2, 14), "Secret Ending: Obsessed with trash");
			//Game ends here, restart everything
			break;
		case 1:
			break;
		}
		break;

	}
	trashCanInteractions++;
}

void InteractionsManager::SofaInteracted(GameObject* sofa, GameObject* player, bool isNothing)
{
}

void InteractionsManager::ShowerInteracted(GameObject* sink, GameObject* player)
{
	timeSystem->increaseTimeTaken(5);
}

void InteractionsManager::SinkInteracted(GameObject* sink, GameObject* player, bool isNothing)
{
}

void InteractionsManager::PlanksInteracted(GameObject* planks, GameObject* player)
{
	timeSystem->increaseTimeTaken(5);
}

void InteractionsManager::ToolboxInteracted(GameObject* box, GameObject* player)
{
	timeSystem->increaseTimeTaken(5);
}

void InteractionsManager::BoxInteracted(GameObject* box, GameObject* player, int random)
{
	timeSystem->increaseTimeTaken(5);
}

void InteractionsManager::StoveInteracted(GameObject* stove, GameObject* player)
{
	timeSystem->increaseTimeTaken(5);
}

void InteractionsManager::KitchenCabinetInteracted(GameObject* kitchenCabinet, GameObject* player)
{
	timeSystem->increaseTimeTaken(5);
}

void InteractionsManager::TrashCanInteracted(GameObject* trashCan, GameObject* player, int random)
{
	Start();
	ui->CreateOptionUI(Vector2(-2, 14), false);
	int choosenItem;
	switch (trashCanInteractions)
	{
	case 0:
		ui->PrintDialogue(Vector2(-2, 14), "A trash can, not remarkable in any way.");
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		choosenItem = ui->PickDialogue(Vector2(-2, 14), "Search the trash can?");
		switch (choosenItem)
		{
		case 0:
			timeSystem->increaseTimeTaken(5);
			ui->PrintDialogue(Vector2(-2, 14), "You searched the trash can and found nothing.");

			break;
		case 1:
			break;
		}
		break;
	case 1:
		ui->PrintDialogue(Vector2(-2, 14), "You've been staring at it for a while, but it's just an ordinary trash can.");
		ui->PrintDialogue(Vector2(-2, 14), "You: Maybe try again?");
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		choosenItem = ui->PickDialogue(Vector2(-2, 14), "Search the trash can?");
		switch (choosenItem)
		{
		case 0:
			timeSystem->increaseTimeTaken(5);
			ui->PrintDialogue(Vector2(-2, 14), "You searched the trash can and found nothing.");

			break;
		case 1:
			break;
		}
		break;
	case 2:
		ui->PrintDialogue(Vector2(-2, 14), "You try to hold back the urge to open it.");
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		choosenItem = ui->PickDialogue(Vector2(-2, 14), "Search the trash can?");
		switch (choosenItem)
		{
		case 0:
			ui->PrintDialogue(Vector2(-2, 14), "As you continue staring at the trash cans, they seem to turn before your very eyes.");
			ui->PrintDialogue(Vector2(-2, 14), "The edges are no longer rusty, and the dents are smoothed over.");
			ui->PrintDialogue(Vector2(-2, 14), "From under the lid comes a faint golden glow, sweet and alluring.");
			ui->PrintDialogue(Vector2(-2, 14), "For a moment, the trash cans turn into treasure chests. … And it's happening again.");
			ui->PrintDialogue(Vector2(-2, 14), "You take a depth breath and open the lid.");
			ui->PrintDialogue(Vector2(-2, 14), "It's empty…");
			ui->PrintDialogue(Vector2(-2, 14), "Wait!");
			ui->PrintDialogue(Vector2(-2, 14), "You reach deeper into the trash can.");
			ui->PrintDialogue(Vector2(-2, 14), "There is still nothing.");
			ui->PrintDialogue(Vector2(-2, 14), "You pry deeper, hoping to find something valuable.");
			ui->PrintDialogue(Vector2(-2, 14), "Time passed, and you didn't notice someone opening the front door and walk behind you.");
			ui->PrintDialogue(Vector2(-2, 14), "???: Just what are you doing?");
			ui->PrintDialogue(Vector2(-2, 14), "You: Who's- ");
			ui->PrintDialogue(Vector2(-2, 14), "Before you could turn around, the mysterious man snaps your neck");
			ui->PrintDialogue(Vector2(-2, 14), "You died.");
			ui->PrintDialogue(Vector2(-2, 14), "Secret Ending: Obsessed with trash");
			//Game ends here, restart everything
			break;
		case 1:
			break;
		}
		break;

	}
	trashCanInteractions++;
}

void InteractionsManager::TableInteracted(GameObject* table, GameObject* player)
{
	timeSystem->increaseTimeTaken(5);
}

void InteractionsManager::PhoneInteracted(GameObject* phone, GameObject* player)
{
	timeSystem->increaseTimeTaken(5);
}

void InteractionsManager::LivingRoomCabinetInteracted(GameObject* livingRoomCabinet, GameObject* player)
{
	timeSystem->increaseTimeTaken(5);
}

void InteractionsManager::BedRoomCabinetInteracted(GameObject* bedRoomCabinet, GameObject* player)
{
	timeSystem->increaseTimeTaken(5);
}

void InteractionsManager::BedInteracted(GameObject* bed, GameObject* player)
{
	//on first loop player will go sleep
	//on second loop onwards player will not sleep
}

void InteractionsManager::TelevisionInteracted(GameObject* bed, GameObject* player)
{
	timeSystem->increaseTimeTaken(5);
}

void InteractionsManager::MainDoorInteracted(GameObject* MainDoor, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(-2, 14), false);
	ui->PrintDialogue(Vector2(-2, 14), "You: Strange, the door can't be opened");


}

void InteractionsManager::BedroomDoorInteracted(GameObject* BedroomDoor, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(-2, 14), false);
	ui->GetOptionUI()->AddOption(new std::string("Yes"));
	ui->GetOptionUI()->AddOption(new std::string("No"));
	int choosenItem = ui->PickDialogue(Vector2(-2, 14), "Enter the BEDROOM?");
	switch (choosenItem)
	{
	case 0:
		timeSystem->increaseTimeTaken(5);
		SceneManager::LoadScene("BedroomScene");
		break;
	case 1:
		break;
	}
}

void InteractionsManager::ClosetDoorInteracted(GameObject* closetDoor, GameObject* player)
{
	timeSystem->increaseTimeTaken(5);
}

void InteractionsManager::KitchenDoorInteracted(GameObject* KitchenDoor, GameObject* player)
{
	timeSystem->increaseTimeTaken(5);
}

void InteractionsManager::ToiletDoorInteracted(GameObject* ToiletDoor, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(-2, 14), false);
	ui->GetOptionUI()->AddOption(new std::string("Yes"));
	ui->GetOptionUI()->AddOption(new std::string("No"));
	int choosenItem = ui->PickDialogue(Vector2(-2, 14), "Enter the TOILET?");
	switch (choosenItem)
	{
	case 0:
		timeSystem->increaseTimeTaken(5);
		SceneManager::LoadScene("ToiletScene");
		break;
	case 1:
			break;
	}
}

void InteractionsManager::LivingRoomDoorInteracted(GameObject* BathroomDoor, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(-2, 14), false);
	ui->GetOptionUI()->AddOption(new std::string("Yes"));
	ui->GetOptionUI()->AddOption(new std::string("No"));
	int choosenItem = ui->PickDialogue(Vector2(-2, 14), "Enter the LIVING ROOM?");
	switch (choosenItem)
	{
	case 0:
		timeSystem->increaseTimeTaken(5);
		SceneManager::LoadScene("LivingRoomScene");
		break;
	case 1:
		break;
	}
}

void InteractionsManager::ToiletCabinetInteracted(GameObject* toiletCabinet, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(-2, 14), false);
	if (hasCabinetKeyCollected)
	{
		timeSystem->increaseTimeTaken(5);
		ui->PrintDialogue(Vector2(-2, 14), "You unlocked the cabinet door!");
		ui->PrintDialogue(Vector2(-2, 14), "You: I got some beta blockers inside that can calm me down");
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		int choosenItem = ui->PickDialogue(Vector2(-2, 14), "Eat beta blockers?");
		switch (choosenItem)
		{
		case 0:
			timeSystem->increaseTimeTaken(5);
			ui->PrintDialogue(Vector2(-2, 14), "You took some beta blockers, you feel calm as ever!");
			break;
		case 1:
			break;
		}
	}
	else
	{
		ui->PrintDialogue(Vector2(-2, 14), "You: I need a key to unlock the cabinet door.");
	}
}

void InteractionsManager::Start()
{
	ui = GameManager::getGM()->gameUI;
}
