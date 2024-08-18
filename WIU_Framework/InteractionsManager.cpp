#define POINTX -105
#define POINTY 25
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
	Start();

	ui->PrintDialogue(Vector2(POINTX, POINTY), "There's some dirty dishes.");
	ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Oops... I should clean that up.");
	ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Later :D");
	timeSystem->increaseTimeTaken(5);
}

void InteractionsManager::PlanksInteracted(GameObject* planks, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	if (hasPlanks)
	{
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I already have the planks.");
	}
	else
	{
		ui->PrintDialogue(Vector2(POINTX, POINTY), "There's some wooden planks on the shelf.");
		switch (timeSystem->TimeLoop)
		{
		case 0:
		case 1:
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I can use that to fix, or block something.");
			break;
		case 2:
			ui->GetOptionUI()->AddOption(new std::string("Yes"));
			ui->GetOptionUI()->AddOption(new std::string("No"));
			int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Take the planks?");
			switch (choosenItem)
			{
			case 0:
				timeSystem->increaseTimeTaken(5);
				hasPlanks = true;
				GameManager::getGM()->inventory.PickupItem("Planks");
				ui->PrintDialogue(Vector2(POINTX, POINTY), "Picked up planks!");
				break;
			case 1:
				break;
			}
		}
	}
}

void InteractionsManager::ToolboxInteracted(GameObject* box, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	if (hasNails and hasHammer)
	{
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I already have the tools.");
	}
	else
	{
		ui->PrintDialogue(Vector2(POINTX, POINTY), "There's only one hammer inside the toolbox, with some nails.");
		switch (timeSystem->TimeLoop)
		{
		case 0:
		case 1:
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I can use those to fix, or block something.");
			break;
		case 2:
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I can use this to barricade the door.");
			ui->GetOptionUI()->AddOption(new std::string("Yes"));
			ui->GetOptionUI()->AddOption(new std::string("No"));
			int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Take the nails and hammer?");
			switch (choosenItem)
			{
			case 0:
				timeSystem->increaseTimeTaken(5);
				hasHammer = true;
				GameManager::getGM()->inventory.PickupItem("Hammer");
				GameManager::getGM()->inventory.PickupItem("Nails");
				ui->PrintDialogue(Vector2(POINTX, POINTY), "Picked up hammer and nails!");
				break;
			case 1:
				break;
			}
		}
	}
}

void InteractionsManager::BoxInteracted(GameObject* box, GameObject* player, int random)
{
	Start();

	ui->PrintDialogue(Vector2(POINTX, POINTY), "There's nothing inside.");
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

	ui->PrintDialogue(Vector2(POINTX, POINTY), "You tried to search the table.");
	ui->PrintDialogue(Vector2(POINTX, POINTY), "But there was nothing on it.");
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

}

void InteractionsManager::LivingRoomCabinetInteracted(GameObject* livingRoomCabinet, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	if (hasDuctTape)
	{
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: There's nothing else inside.");
	}
	else
	{
		ui->PrintDialogue(Vector2(POINTX, POINTY), "Inside the big cabinet, there's only a roll of duct tape.");
		switch (timeSystem->TimeLoop)
		{
		case 0:
		case 1:
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Why did I put this here...");
			break;
		case 2:
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I can use this to tie the killer up.");
			ui->GetOptionUI()->AddOption(new std::string("Yes"));
			ui->GetOptionUI()->AddOption(new std::string("No"));
			int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Take the duct tape?");
			switch (choosenItem)
			{
			case 0:
				timeSystem->increaseTimeTaken(5);
				hasHammer = true;
				GameManager::getGM()->inventory.PickupItem("Duct Tape");
				ui->PrintDialogue(Vector2(POINTX, POINTY), "Picked up a roll of duct tape!");
				break;
			case 1:
				break;
			}
		}
	}
}

void InteractionsManager::ClosetDoorInteracted(GameObject* bedRoomCabinet, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);

	timeSystem->increaseTimeTaken(5);
	switch (timeSystem->TimeLoop) 
	{

		case 0:
		case 1:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I locked this up to keep the valuables safe.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I wonder where I put the keys at... I kinda forgot.");

		break;
		default:
			ui->CreateOptionUI(Vector2(POINTX, POINTY), false);

			if (hasClosetKeyCollected)
			{
				ui->PrintDialogue(Vector2(POINTX, POINTY), "The closet seems big enough for a person to hide inside.");
				ui->GetOptionUI()->AddOption(new std::string("Yes"));
				ui->GetOptionUI()->AddOption(new std::string("No"));
				int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Hide inside?");
				switch (choosenItem)
				{
				case 0:
					ui->PrintDialogue(Vector2(POINTX, POINTY), "You hid inside.");
					//closet endings, differ if player has knife/pan and duct tape
					break;
				case 1:
					ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Seems like a bad idea...");

					break;
				}
			}
			else
			{
				ui->PrintDialogue(Vector2(POINTX, POINTY), "I don't have the key.");
			}
			
	}
}

void InteractionsManager::BedRoomDrawerInteracted(GameObject* bedRoomCabinet, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	ui->PrintDialogue(Vector2(POINTX, POINTY), "There is some stuff in the drawer.");
	ui->PrintDialogue(Vector2(POINTX, POINTY), "It's quite messy.");
	ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I should really clean this up...");
	ui->GetOptionUI()->AddOption(new std::string("Yes"));
	ui->GetOptionUI()->AddOption(new std::string("No"));
	int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Organise the drawer?");
	int choosenInput;
	switch (choosenItem)
	{
	case 0:
		ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
		timeSystem->increaseTimeTaken(5);
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You cleaned up the drawer.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "While you were organizing, you found a key inside.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I wonder what this key is used for...");
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		choosenInput = ui->PickDialogue(Vector2(POINTX, POINTY), "Keep the key?");
		switch (choosenInput)
		{
			case 0:
				hasClosetKeyCollected = true;
				GameManager::getGM()->inventory.PickupItem("Unknown Key");
				ui->PrintDialogue(Vector2(POINTX, POINTY), "Picked up a key But you don't know what is it for...");
				break;
			case 1:
				ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I don't think I have any use of this.");
				break;
		}
		break;
	case 1:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I don't think I have time for this.");
		break;
	}
}

void InteractionsManager::BedInteracted(GameObject* bed, GameObject* player)
{
	//on first loop player will go sleep
	//on second loop onwards player will not sleep

	Start();
	ui->CreateOptionUI(Vector2(POINTX, 13), false);
	switch (timeSystem->TimeLoop)
	{
	case 0:
	case 1:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You went to sleep.");
		// play first loop ending
		break;
	default:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I can't sleep...");
		break;
	}
}

void InteractionsManager::TelevisionInteracted(GameObject* bed, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	ui->PrintDialogue(Vector2(POINTX, POINTY), "TV: BREAKING NEWS, A SERIAL KILLER IS ON THE LOOSE, PLEASE CHECK YOUR LOCKS AND KEEP YOURSELF SAFE!");
}

void InteractionsManager::MainDoorInteracted(GameObject* MainDoor, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(POINTX, 13), false);
	switch (timeSystem->TimeLoop)
	{
	case 0:
	case 1:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Strange... I can't open the door.");
		break;
	default:
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

void InteractionsManager::KitchenDoorInteracted(GameObject* KitchenDoor, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	ui->GetOptionUI()->AddOption(new std::string("Yes"));
	ui->GetOptionUI()->AddOption(new std::string("No"));
	int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Enter the KITCHEN?");
	switch (choosenItem)
	{
	case 0:
		timeSystem->increaseTimeTaken(5);
		SceneManager::LoadScene("KitchenScene");
		break;
	case 1:
		break;
	}
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

void InteractionsManager::StoreRoomDoorInteracted(GameObject* storeRoomDoor, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);

	if (hasStoreRoomKeyCollected)
	{
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Enter the STORE ROOM?");
		switch (choosenItem)
		{
		case 0:
			timeSystem->increaseTimeTaken(5);
			SceneManager::LoadScene("StoreRoomScene");
			break;
		case 1:
			break;
		}
	}
	else
	{
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I need a key to unlock the store room.");
	}
}

void InteractionsManager::ClockInteracted(GameObject* clock, GameObject* player)
{
	// show the current time
	Start();
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	ui->PrintDialogue(Vector2(POINTX, POINTY), "The time is currently: ");
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
