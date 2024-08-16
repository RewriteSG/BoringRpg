#define POINTX -2
#define POINTY 13
#include "InteractionsManager.h"
#include "GameManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "Furniture.h"


InteractionsManager::InteractionsManager() : timeSystem(nullptr), ui(nullptr)
{
	hasCabinetKeyCollected = false;
	hasCalledTheCops = false;
	hasClosetKeyCollected = false;
	hasDuctTape = false;
	hasHammer = false;
	hasKnife = false;
	hasMetalPan = false;
	hasPlanks = false;
	hasNails = false;
	hasShampoo = false;
	hasStoreRoomKeyCollected = false;
	isDoorBarricaded = false;
}

void InteractionsManager::SofaInteracted(GameObject* sofa, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	if (hasStoreRoomKeyCollected) 
	{
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I don't think there is anything else I can do here.");
	}
	else 
	{
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I remember hiding my storeroom key under the sofa so no one can find it.");
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Take the key?");
		switch (choosenItem)
		{
		case 0:
			timeSystem->increaseTimeTaken(5);
			hasStoreRoomKeyCollected = true;
			GameManager::getGM()->inventory.PickupItem("StoreRoom Key");
			ui->PrintDialogue(Vector2(POINTX, POINTY), "Picked up storeroom key!");
			break;
		case 1:
			break;
		}
	}

}

void InteractionsManager::SofaInteracted(GameObject* sofa, GameObject* player, bool isNothing)
{
}

void InteractionsManager::ShowerInteracted(GameObject* shower, GameObject* player)
{
	ui->PrintDialogue(Vector2(POINTX, POINTY), "Just a normal shower.");
	switch (timeSystem->TimeLoop)
	{
	case 0:
	case 1:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I used to hide behind the shower during hide and seek when I was younger.");
		break;
	default:

		ui->CreateOptionUI(Vector2(POINTX, POINTY), false);

		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I can probably hide here.");
		ui->GetOptionUI()->AddOption(new std::string("Hide"));
		ui->GetOptionUI()->AddOption(new std::string("Don't hide"));
		int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Hide behind the shower?");
		switch (choosenItem)
		{
		case 0:
			//trigger hiding in bathroom ending
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You hid in the shower."); //remove this later
			break;
		case 1:
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Bad idea.");
			break;
		}
		break;
	}
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
	Start();
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	if (hasMetalPan)
	{
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I don't think there is anything else I can do here.");
	}
	else
	{
		ui->PrintDialogue(Vector2(POINTX, POINTY), "There's a pan at the top of the stove.");
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Take the pan?");
		switch (choosenItem)
		{
		case 0:
			timeSystem->increaseTimeTaken(5);
			hasMetalPan = true;
			GameManager::getGM()->inventory.PickupItem("Metal Pan");
			ui->PrintDialogue(Vector2(POINTX, POINTY), "Picked up metal pan!");
			break;
		case 1:
			break;
		}
	}
}

void InteractionsManager::KitchenCabinetInteracted(GameObject* kitchenCabinet, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	if (hasKnife)
	{
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I don't think there is anything else I can do here.");
	}
	else
	{
		ui->PrintDialogue(Vector2(POINTX, POINTY), "There's some knives in the cabinet.");
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Take the knife?");
		switch (choosenItem)
		{
		case 0:
			timeSystem->increaseTimeTaken(5);
			hasKnife = true;
			GameManager::getGM()->inventory.PickupItem("Kitchen knife");
			ui->PrintDialogue(Vector2(POINTX, POINTY), "Picked up knife!");
			break;
		case 1:
			break;
		}
	}
}

void InteractionsManager::TrashCanInteracted(GameObject* trashCan, GameObject* player, int random)
{
	Start();
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	int choosenItem;
	switch (trashCanInteractions)
	{
	case 0:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "A trash can, not remarkable in any way.");
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Search the trash can?");
		switch (choosenItem)
		{
		case 0:
			timeSystem->increaseTimeTaken(5);
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You searched the trash can and found nothing.");

			break;
		case 1:
			trashCanInteractions--;
			break;
		}
		break;
	case 1:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You've been staring at it for a while, but it's just an ordinary trash can.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Maybe try again?");
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Search the trash can?");
		switch (choosenItem)
		{
		case 0:
			timeSystem->increaseTimeTaken(5);
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You searched the trash can and found nothing.");

			break;
		case 1:
			trashCanInteractions--;
			break;
		}
		break;
	case 2:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You try to hold back the urge to open it.");
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Search the trash can?");
		switch (choosenItem)
		{
		case 0:
			timeSystem->increaseTimeTaken(5);
			ui->PrintDialogue(Vector2(POINTX, POINTY), "As you continue staring at the trash cans, they seem to turn before your very eyes.");
			ui->PrintDialogue(Vector2(POINTX, POINTY), "The edges are no longer rusty, and the dents are smoothed over.");
			ui->PrintDialogue(Vector2(POINTX, POINTY), "From under the lid comes a faint golden glow, sweet and alluring.");
			ui->PrintDialogue(Vector2(POINTX, POINTY), "For a moment, the trash cans turn into treasure chests. ...And it's happening again.");
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You take a depth breath and open the lid.");
			ui->PrintDialogue(Vector2(POINTX, POINTY), "It's empty...");
			ui->PrintDialogue(Vector2(POINTX, POINTY), "Wait!");
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You reach deeper into the trash can.");
			ui->PrintDialogue(Vector2(POINTX, POINTY), "There is still nothing.");
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You pry deeper, hoping to find something valuable.");
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You: ...");
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You: WTF am I doing...");
			ui->PrintDialogue(Vector2(POINTX, POINTY), "Secret Ending: Instincts");
			//Game ends here, restart everything
			break;
		case 1:
			trashCanInteractions--;
			break;
		}
	default:
	{
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I should stop.");
	}
		break;
	}
	trashCanInteractions++;
}

void InteractionsManager::TableInteracted(GameObject* table, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);

	ui->PrintDialogue(Vector2(POINTX, POINTY), "You: There is nothing on the table.");
	timeSystem->increaseTimeTaken(5);
}

void InteractionsManager::BedroomTableInteracted(GameObject* bedroomTable, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	ui->PrintDialogue(Vector2(POINTX, POINTY), "There is a bunch of stuff on the table.");
	ui->GetOptionUI()->AddOption(new std::string("Photograph"));
	ui->GetOptionUI()->AddOption(new std::string("Phone"));
	ui->GetOptionUI()->AddOption(new std::string("Music Box"));
	ui->GetOptionUI()->AddOption(new std::string("Nothing"));
	int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Which one should you check out?");

	switch (choosenItem)
	{
	case 0:
		timeSystem->increaseTimeTaken(5);
		ui->PrintDialogue(Vector2(POINTX, POINTY), "A photo of your family.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I miss them...");
		break;
	case 1:
		timeSystem->increaseTimeTaken(5);
		switch (timeSystem->TimeLoop)
		{ 
		case 0:
		case 1:
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I left my phone on the table today.");
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I should remember that next time.");
			break;
		default:

			ui->CreateOptionUI(Vector2(POINTX, POINTY), false);

			ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I should probably call the cops.");
			ui->GetOptionUI()->AddOption(new std::string("Call the cops"));
			ui->GetOptionUI()->AddOption(new std::string("Don't call the cops"));
			int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Call the cops?");
			switch (choosenItem)
			{
			case 0:
				if (!hasCalledTheCops)
				{
					ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
					hasCalledTheCops = true;
					timeSystem->increaseTimeTaken(5);
					ui->PrintDialogue(Vector2(POINTX, POINTY), "You called the cops.");
					ui->PrintDialogue(Vector2(POINTX, POINTY), "Cops: Hi, this is [REDACTED] police department, how may I help?");
					ui->PrintDialogue(Vector2(POINTX, POINTY), "You: YOU GOTTA SEND SOMEONE HERE!");
					ui->PrintDialogue(Vector2(POINTX, POINTY), "You: THERE IS A SERIAL KILLER ON THE LOOSE AND HE IS COMING FOR ME!");
					ui->PrintDialogue(Vector2(POINTX, POINTY), "Cops: Okay stay calm, help is on their way and will be there at 12:15.");
					ui->PrintDialogue(Vector2(POINTX, POINTY), "You: BUT I DON'T HAVE MUCH-");
					ui->PrintDialogue(Vector2(POINTX, POINTY), "They hung up.");
					ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Son of a-");
					ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I guess that I have to find a way to hold him off until they come.");
					break;
				}
				else
				{
					ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I already called the cops.");
					break;
				}
			case 1:
				ui->PrintDialogue(Vector2(POINTX, POINTY), "They wouldn't believe me.");
				ui->PrintDialogue(Vector2(POINTX, POINTY), "Only I can help myself now.");
				break;
			}
			break;
		}

		break;
	case 2:
		timeSystem->increaseTimeTaken(5);
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You winded up the music box, and it played a song.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: This was my favourite toy when I was a kid.");
		break;

	default:
		break;
	}

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
	ui->CreateOptionUI(Vector2(POINTX, 13), false);
	if (hasHammer && hasPlanks && hasNails)
	{
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I could barricade the door, this can buy some time.");
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Barricade the door with PLANKS and NAILS?");
		switch (choosenItem)
		{
		case 0:
			timeSystem->increaseTimeTaken(5);
			isDoorBarricaded = true;
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You: There, all good.");
			ui->PrintDialogue(Vector2(POINTX, POINTY), "Successfully barricaded the door!");
			break;
		case 1:
			break;
		}
	}
	if (hasShampoo)
	{
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I could make the entrance slippery, this can buy some time.");
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Make the entrance slippery with SHAMPOO?");
		switch (choosenItem)
		{
		case 0:
			timeSystem->increaseTimeTaken(5);
			isDoorBarricaded = true;
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You: There, all good.");
			ui->PrintDialogue(Vector2(POINTX, POINTY), "Successfully made the floor slippery!");
			break;
		case 1:
			break;
		}
	}
	else
	{
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Strange, the door can't be opened");
	}
}

void InteractionsManager::BedroomDoorInteracted(GameObject* BedroomDoor, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	ui->GetOptionUI()->AddOption(new std::string("Yes"));
	ui->GetOptionUI()->AddOption(new std::string("No"));
	int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Enter the BEDROOM?");
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
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	ui->GetOptionUI()->AddOption(new std::string("Yes"));
	ui->GetOptionUI()->AddOption(new std::string("No"));
	int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Enter the TOILET?");
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
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	ui->GetOptionUI()->AddOption(new std::string("Yes"));
	ui->GetOptionUI()->AddOption(new std::string("No"));
	int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Enter the LIVING ROOM?");
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
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	if (hasCabinetKeyCollected)
	{
		timeSystem->increaseTimeTaken(5);
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You unlocked the cabinet door!");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I got some beta blockers inside that can calm me down");
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Eat beta blockers?");
		switch (choosenItem)
		{
		case 0:
			timeSystem->increaseTimeTaken(5);
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You took some beta blockers, you feel calm as ever!");
			break;
		case 1:
			break;
		}
	}
	else
	{
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I need a key to unlock the cabinet door.");
	}
}

void InteractionsManager::Start()
{
	ui = GameManager::getGM()->gameUI;
	timeSystem = &GameManager::getGM()->TimeSys;

}

//robber interaction

//void InteractionsManager::robBedroomDoorInteracted(GameObject* BedroomDoor, GameObject* robber)
//{
	//timer.increaseTimeTaken(5);
//}
