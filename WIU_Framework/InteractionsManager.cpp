#define POINTX -105
#define POINTY 25
#include "InteractionsManager.h"
#include "GameManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "Furniture.h"
#include "ObjectivesManager.h"
#include "Application.h"

void InteractionsManager::SeperateInput(std::string input, std::string& input1, std::string& input2)
{
	int chCount = 0;
	bool space = false;
	for (char ch : input)
	{
		if (ch == ' ')
		{
			space = true;
			//chCount++;
			break;
		}
		else
			chCount++;
	}

	input1 = input.substr(0, chCount); 
	if (space)
		input2 = input.substr(chCount+1);
	else
		input2 = "";
}

InteractionsManager::InteractionsManager() : timeSystem(nullptr), ui(nullptr)
{
	isPlayerHidden = false;
	isSoapSetup = false;
	isBarricadeSetup = false;



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
	ui->PrintDialogue(Vector2(POINTX, POINTY), "Just a normal shower."); int choosenItem =0;
	bool* hasTakenShower = &(GameManager::getGM()->objManager).hasTakenShower;

	switch (timeSystem->TimeLoop)
	{
	case 0:
	case 1:

		ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Take a shower?");
		switch (choosenItem)
		{
		case 0:
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You took a shower.");
			*hasTakenShower = true;
			break;
		case 1:
			break;
		}
		break;
	default:

		ui->CreateOptionUI(Vector2(POINTX, POINTY), false);

		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I can probably hide here.");
		ui->GetOptionUI()->AddOption(new std::string("Hide"));
		ui->GetOptionUI()->AddOption(new std::string("Don't hide"));
		choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Hide behind the shower?");
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
		default:
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
		default:
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
				ui->GetOptionUI()->AddOption(new std::string("Hide"));
				ui->GetOptionUI()->AddOption(new std::string("Leave"));
				int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Hide inside?");
				switch (choosenItem)
				{
				case 0:
					ui->PrintDialogue(Vector2(POINTX, POINTY), "You hid inside.");		
					isPlayerHidden = true;
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
	Start();
	ui->CreateOptionUI(Vector2(POINTX, 13), false);

	bool* hasSlept = &(GameManager::getGM()->objManager).hasSlept;
	switch (timeSystem->TimeLoop)
	{
	case 0:
	case 1:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You went to sleep.");
		*hasSlept = true;
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
<<<<<<< HEAD
	ui->PrintDialogue(Vector2(POINTX, POINTY), "TV: BREAKING BREAKING NEWS, A SERIAL KILLER IS ON THE LOOSE, PLEASE CHECK YOUR LOCKS AND KEEP YOURSELF SAFE!");
=======

	bool* hasWatchedTV = &(GameManager::getGM()->objManager).hasWatchedTV;
	switch (timeSystem->TimeLoop)
	{
	case 0:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You turned on the TV.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "TV: BREAKING NEWS, A SERIAL KILLER IS ON THE LOOSE, PLEASE CHECK YOUR LOCKS AND KEEP YOURSELF SAFE!");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Serial killer? Not really my problem, it's not like he would target me anyways.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I should go to bed now.");
		*hasWatchedTV = true;
		break;
	case 1:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You turned on the TV.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "TV: BREAKING NEWS, A SERIAL KILLER IS ON THE LOOSE, PLEASE CHECK YOUR LOCKS AND KEEP YOURSELF SAFE!");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Did they run out of news? This is literally the same as yesterday!");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Nevermind, I should just find some other things to do now.");
		*hasWatchedTV = true;
		break;
	default:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You turned on the TV.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "TV: BREAKING NEWS, A SERIAL KILLER IS ON THE LOOSE, PLEASE CHECK YOUR LOCKS AND KEEP YOURSELF SAFE!");
		*hasWatchedTV = true;
		break;
	}
>>>>>>> Prototype-ver-1.6
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

			ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Strange, the door can't be opened");
		
	}
}

void InteractionsManager::BedroomDoorInteracted(GameObject* BedroomDoor, GameObject* player)
{
		SceneManager::LoadScene("BedroomScene");
	//Start();
	//ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	//ui->GetOptionUI()->AddOption(new std::string("Yes"));
	//ui->GetOptionUI()->AddOption(new std::string("No"));
	//int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Enter the BEDROOM?");
	//switch (choosenItem)
	//{
	//case 0:
	//	timeSystem->increaseTimeTaken(5);
	//	break;
	//case 1:
	//	break;
	//}
}

void InteractionsManager::KitchenDoorInteracted(GameObject* KitchenDoor, GameObject* player)
{
		SceneManager::LoadScene("KitchenScene");
	//Start();
	//ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	//ui->GetOptionUI()->AddOption(new std::string("Yes"));
	//ui->GetOptionUI()->AddOption(new std::string("No"));
	//int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Enter the KITCHEN?");
	//switch (choosenItem)
	//{
	//case 0:
	//	timeSystem->increaseTimeTaken(5);
	//	break;
	//case 1:
	//	break;
	//}
}

void InteractionsManager::ToiletDoorInteracted(GameObject* ToiletDoor, GameObject* player)
{
		SceneManager::LoadScene("ToiletScene");
	//Start();
	//ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	//ui->GetOptionUI()->AddOption(new std::string("Yes"));
	//ui->GetOptionUI()->AddOption(new std::string("No"));
	//int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Enter the TOILET?");
	//switch (choosenItem)
	//{
	//case 0:
	//	timeSystem->increaseTimeTaken(5);
	//	break;
	//case 1:
	//		break;
	//}

}

void InteractionsManager::LivingRoomDoorInteracted(GameObject* BathroomDoor, GameObject* player)
{
		SceneManager::LoadScene("LivingRoomScene");
	//Start();
	//ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	//ui->GetOptionUI()->AddOption(new std::string("Yes"));
	//ui->GetOptionUI()->AddOption(new std::string("No"));
	//int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Enter the LIVING ROOM?");
	//switch (choosenItem)
	//{
	//case 0:
	//	timeSystem->increaseTimeTaken(5);
	//	break;
	//case 1:
	//	break;
	//}
}

void InteractionsManager::StoreRoomDoorInteracted(GameObject* storeRoomDoor, GameObject* player)
{
	Start();
	//ui->CreateOptionUI(Vector2(POINTX, POINTY), false);

	if (hasStoreRoomKeyCollected)
	{

		SceneManager::LoadScene("StoreRoomScene");
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
	ui->PrintDialogue(Vector2(POINTX, POINTY), "The time is currently: " +
		GameManager::getGM()->TimeSys.GetTimeinString(GameManager::getGM()->TimeSys.TimeTaken));
}

bool InteractionsManager::UseItem(std::string useItem, GameObject* player)
{
	UI ui(Vector2(Application::numberOfColumns / 2 - 171 / 2, 35), 0, 171);

	std::string keyword;
	std::string useItem1; 
	std::string useItem2; 
	std::string useItem3; 
	
	SeperateInput(useItem, useItem1, keyword);
	SeperateInput(keyword, keyword, useItem2);
	if (!GameManager::getGM()->inventory.InventoryHasItems(useItem1))
	{
		GameManager::getGM()->ClearDialogue();
		ui.PrintDialogue(Vector2(2,2), "No " + useItem1 + " in Inventory");
		return false;
	}
	if(keyword != "with" && keyword.length() > 0)
	{

		GameManager::getGM()->ClearDialogue();
		ui.PrintDialogue(Vector2(2,2), "Invalid Input");
		return false;
	}
	else if (keyword == "with")
	{
		SeperateInput(useItem2, useItem2, keyword); 
		SeperateInput(keyword, keyword, useItem3); 
		if (!GameManager::getGM()->inventory.InventoryHasItems(useItem2) ) 
		{

			GameManager::getGM()->ClearDialogue(); 
			ui.PrintDialogue(Vector2(2,2), "No " + useItem2 + " in Inventory");
			return false;
		}
		if (keyword != "with" && keyword.length() > 0)
		{
			GameManager::getGM()->ClearDialogue();
			ui.PrintDialogue(Vector2(2,2), "Invalid Input");
			return false;
		}
		else if (keyword == "with")
		{
			if (!GameManager::getGM()->inventory.InventoryHasItems(useItem3)) 
			{
				GameManager::getGM()->ClearDialogue();
				ui.PrintDialogue(Vector2(2,2), "No " + useItem3 + " in Inventory");
				return false;
			}
		}
	}



	Furniture* furnituresLeft, * furnituresRight, * furnituresUp, * furnituresDown;
	furnituresLeft = dynamic_cast<Furniture*>(SceneManager::currentScene->GetObjectManager()->GetObjectAtPosition(Vector2(player->GetPosition()->GetX() - 1, player->GetPosition()->GetY())));
	furnituresRight = dynamic_cast<Furniture*>(SceneManager::currentScene->GetObjectManager()->GetObjectAtPosition(Vector2(player->GetPosition()->GetX() + 1, player->GetPosition()->GetY())));
	furnituresUp = dynamic_cast<Furniture*>(SceneManager::currentScene->GetObjectManager()->GetObjectAtPosition(Vector2(player->GetPosition()->GetX(), player->GetPosition()->GetY() - 1)));
	furnituresDown = dynamic_cast<Furniture*>(SceneManager::currentScene->GetObjectManager()->GetObjectAtPosition(Vector2(player->GetPosition()->GetX(), player->GetPosition()->GetY() + 1)));
	
	ui.CreateText("Use item(s) on what? Enter 'on <Object Name>'", Vector2(2, 2)); 
	GameManager::getGM()->DisplayFurnituresAroundPlayer(Vector2(2, 3)); //print at (2,3);
	std::string input = GameManager::getGM()->InputField(); 
	//int itemsUsing = 0;
	if (furnituresRight) 
	{
		if (furnituresRight->GetFurnitureType() == Furniture::MainDoor && (input == "on door" || input == "on main door" || input == "on main"))
		{
			bool usingNails = useItem1 == "nails" || useItem2 == "nails" || useItem3 == "nails"; 
			bool usingPlanks = useItem1 == "planks" || useItem2 == "planks" || useItem3 == "planks";
			bool usingHammer = useItem1 == "hammer" || useItem2 == "hammer" || useItem3 == "hammer"; 

			if (usingHammer && usingNails && usingPlanks)
			{
				GameManager::getGM()->ClearDialogue();
				ui.PrintDialogue(Vector2(2, 2), "Using Nails, Planks and Hammer on the main door.");
				ui.PrintDialogue(Vector2(2,2), "You: I could barricade the door, this can buy some time.");
				timeSystem->increaseTimeTaken(50);
				isDoorBarricaded = true; 
				ui.PrintDialogue(Vector2(2,2), "You: There, all good.");
				ui.PrintDialogue(Vector2(2,2), "Successfully barricaded the door!");
				GameManager::getGM()->inventory.UseItem(useItem1);
				GameManager::getGM()->inventory.UseItem(useItem2);
				GameManager::getGM()->inventory.UseItem(useItem3);
			}
			else 
			{
				GameManager::getGM()->ClearDialogue();
				ui.PrintDialogue(Vector2(2,2), "I dont have enough items to use on the main door!");
			}
			return true;
		}

	}

	return false;
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

void InteractionsManager::Start(bool isGameStarted)
{
	ObjectivesManager* objManager = &(GameManager::getGM()->objManager);
	//Start();
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	switch (timeSystem->TimeLoop)
	{
	case 0:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "I should take a shower first.");
		break;
	case 1:
		objManager->hasTakenShower = false;
		objManager->hasWatchedTV = false;
		objManager->hasSlept = false;

		ui->PrintDialogue(Vector2(POINTX, POINTY), "Huh? How am I here? I remember being asleep.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "Did overworking make me so tired that I lost my memory for the day?");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "Whatever, I don't want to think too much.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "Strange, I don't feel tired though...so I don't think I can sleep.");
		break;
	case 2:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You appear at the door again");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: WHAT WAS THAT!? I JUST GOT KILLED IN MY HOUSE!");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You quickly calm down and think about the situation.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You turned on the TV, and it is showing the same news.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You realized that you are stuck in a time loop of getting killed over and over.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I have to do something about this...");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: He comes at 12:12, I still have time.");
		break;
	default:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Im back again...");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Whatever I did last time didn't work.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: There has to be a way out of this.");
	}
}

void InteractionsManager::Reset(void)
{

}

//robber interaction

//void InteractionsManager::robBedroomDoorInteracted(GameObject* BedroomDoor, GameObject* robber)
//{
	//timer.increaseTimeTaken(5);
//}
