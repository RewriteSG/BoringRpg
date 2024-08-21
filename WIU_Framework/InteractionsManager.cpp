#define POINTX -105
#define POINTY 25
#include "InteractionsManager.h"
#include "GameManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "Furniture.h"
#include "ObjectivesManager.h"
#include "Application.h"
#include "Windows.h"
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
		input2 = input.substr(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(chCount) + 1);
	else
		input2 = "";
}

InteractionsManager::InteractionsManager() : timeSystem(nullptr), ui(nullptr)
{
	isPlayerHidden = false;
	isNailSetup = false;
	isPlankSetup = false;
	isSoapSetup = false;
	isBarricadeSetup = false;
	isPlayerSleeping = false;
	isPlayerSucide = false;

	isClosetUnlocked = false;
	isStoreRoomUnlocked = false;
	hasCabinetKeyCollected = false;
	hasCalledTheCops = false;
	hasClosetKeyCollected = false;
	isPlayerSucide = false;
	hasDuctTape = false;
	hasHammer = false;
	hasKnife = false;
	hasMetalPan = false;
	hasPlanks = false;
	hasNails = false;
	hasSoap = false;
	hasStoreRoomKeyCollected = false;
	isDoorBarricaded = false;
}

void InteractionsManager::SofaInteracted(GameObject* sofa, GameObject* player)
{
	SofaImage();  
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
			GameManager::getGM()->inventory.PickupItem("StoreRoomKey");
			KeyImage();
			ui->PrintDialogue(Vector2(POINTX, POINTY), "Picked up storeroom key!");
			break;
		case 1:
			break;
		}
	}

}

void InteractionsManager::SofaInteracted(GameObject* sofa, GameObject* player, bool isNothing)
{
	SofaImage();
	ui->PrintDialogue(Vector2(POINTX, POINTY), "There's nothing on the sofa.");
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

		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Lets see what can I do here.");
		ui->GetOptionUI()->AddOption(new std::string("Hide"));
		ui->GetOptionUI()->AddOption(new std::string("Search"));
		ui->GetOptionUI()->AddOption(new std::string("Leave"));
		choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "What to do?");
		switch (choosenItem)
		{
		case 0:
			//trigger hiding in bathroom ending
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You hid in the shower."); //remove this later
			isPlayerHidden = true;
			break;
		case 1:
			ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You found a bar of soap.");
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Maybe there's a use to this?");
			ui->GetOptionUI()->AddOption(new std::string("Yes"));
			ui->GetOptionUI()->AddOption(new std::string("No"));
			choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Take the soap");
			switch (choosenItem)
			{
			case 0:
				timeSystem->increaseTimeTaken(5);
				hasSoap = true;
				GameManager::getGM()->inventory.PickupItem("Soap");
				ui->PrintDialogue(Vector2(POINTX, POINTY), "Picked up soap!");
				break;
			case 1:
				break;
			}
			break;
		}
		break;
	}
}

void InteractionsManager::SinkInteracted(GameObject* sink, GameObject* player, bool isNothing)
{
	Start();
	SinkImage();
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
		PlanksImage(true);
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I already have the planks.");
	}
	else
	{
		PlanksImage();
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
				PlanksItemImage();
				ui->PrintDialogue(Vector2(POINTX, POINTY), "Picked up planks!");
				PlanksImage(true);
				Sleep(500);
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
		ToolboxImage(true);
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I already have the tools.");
	}
	else
	{
		ui->PrintDialogue(Vector2(POINTX, POINTY), "There is a toolbox inside this box.");
		ToolboxImage();
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
				hasNails = true;
				GameManager::getGM()->inventory.PickupItem("Hammer");
				GameManager::getGM()->inventory.PickupItem("Nails");
				HammerAndNailsImage();
				ui->PrintDialogue(Vector2(POINTX, POINTY), "Picked up hammer and nails!");
				ToolboxImage(true);
				Sleep(500);
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
	EmptyBoxImage();
	ui->PrintDialogue(Vector2(POINTX, POINTY), "There's nothing inside.");
	timeSystem->increaseTimeTaken(5);
}

void InteractionsManager::StoveInteracted(GameObject* stove, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	if (hasMetalPan)
	{
		StoveImage(true);
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I don't think there is anything else I can do here.");
	}
	else
	{
		StoveImage();
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
		KitchenCabinetImage(true);
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I don't think there is anything else I can do here.");
	}
	else
	{
		KitchenCabinetImage();
		ui->PrintDialogue(Vector2(POINTX, POINTY), "There's some knives in the cabinet.");
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Take the knife?");
		switch (choosenItem)
		{
		case 0:
			timeSystem->increaseTimeTaken(5);
			hasKnife = true;
			KnifeImage();
			GameManager::getGM()->inventory.PickupItem("knife");
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
	TrashCanImage();
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
	TableImage();
	ui->PrintDialogue(Vector2(POINTX, POINTY), "You tried to search the table.");
	ui->PrintDialogue(Vector2(POINTX, POINTY), "But there was nothing on it.");
	timeSystem->increaseTimeTaken(5);
}

void InteractionsManager::BedroomTableInteracted(GameObject* bedroomTable, GameObject* player)
{
	Start();
	BedroomTableImage();
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
			ui->GetOptionUI()->AddOption(new std::string("Yes"));
			ui->GetOptionUI()->AddOption(new std::string("No"));
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
	Start();
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	if (hasDuctTape)
	{
		LivingRoomCabinetImage(true);
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: There's nothing else inside.");
	}
	else
	{
		LivingRoomCabinetImage();
		ui->PrintDialogue(Vector2(POINTX, POINTY), "Inside the big cabinet, there's only a roll of duct tape.");
		switch (timeSystem->TimeLoop)
		{
		case 0:
		case 1:
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Why did I put this here...");
			break;
		default:
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I can use this to tie the killer up.");
			ui->GetOptionUI()->AddOption(new std::string("Yes"));
			ui->GetOptionUI()->AddOption(new std::string("No"));
			int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Take the duct tape?");
			switch (choosenItem)
			{
			case 0:
				timeSystem->increaseTimeTaken(5);
				hasDuctTape = true;
				GameManager::getGM()->inventory.PickupItem("Duct Tape");
				DuctTapeImage();
				ui->PrintDialogue(Vector2(POINTX, POINTY), "Picked up a roll of duct tape!");
				LivingRoomCabinetImage(true); 
				Sleep(500);
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
	ClosetDoorImage();
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
				ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I don't have the key for this.");
			}
			
	}
}

void InteractionsManager::BedRoomDrawerInteracted(GameObject* bedRoomCabinet, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
	if (!hasClosetKeyCollected) {

		BedRoomDrawerImage();
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
			BedRoomDrawerImage(true);
			ui->PrintDialogue(Vector2(POINTX, POINTY), "While you were organizing, you found a key inside.");
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I wonder what this key is used for...");
			ui->GetOptionUI()->AddOption(new std::string("Yes"));
			ui->GetOptionUI()->AddOption(new std::string("No"));
			choosenInput = ui->PickDialogue(Vector2(POINTX, POINTY), "Keep the key?");
			switch (choosenInput)
			{
			case 0:
				hasClosetKeyCollected = true;
				GameManager::getGM()->inventory.PickupItem("UnknownKey");
				ui->PrintDialogue(Vector2(POINTX, POINTY), "Picked up a key But you don't know what is it for...");
				KeyImage();
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
	else 
	{
		BedRoomDrawerImage(true);

		ui->PrintDialogue(Vector2(POINTX, POINTY), "Seems like the drawer is organized already.");

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
		BedImage();
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You went to sleep.");
		*hasSlept = true;
		isPlayerSleeping
		= true;
		GameManager::getGM()->firstLoop = false;
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

	TelevisionImage();
	bool* hasWatchedTV = &(GameManager::getGM()->objManager).hasWatchedTV;
	switch (timeSystem->TimeLoop)
	{
	case 0:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You turned on the TV.");
		TelevisionImage(true);
		ui->PrintDialogue(Vector2(POINTX, POINTY), "TV: BREAKING NEWS, A SERIAL KILLER IS ON THE LOOSE AROUND KRANJI ROAD, PLEASE CHECK YOUR LOCKS AND KEEP YOURSELF SAFE!");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Serial killer? Not really my problem, it's not like he would target me anyways.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: It's quite near my house though...");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Nevermind, surely the police are already on their way to catch him.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Nothing bad will happen.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: By tomorrow morning he should be caught.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I should go to bed now.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You turned off the TV.");
		TelevisionImage(); 
		*hasWatchedTV = true;
		break;
	case 1:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You turned on the TV.");
		TelevisionImage(true);
		ui->PrintDialogue(Vector2(POINTX, POINTY), "TV: BREAKING NEWS, A SERIAL KILLER IS ON THE LOOSE AROUND KRANJI ROAD, PLEASE CHECK YOUR LOCKS AND KEEP YOURSELF SAFE!");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Did they run out of news? This is literally the same as yesterday!");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Are they just that lazy?");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Someone is gonna get fired.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Nevermind, I should just find some other things to do now.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You turned off the TV.");
		TelevisionImage();
		*hasWatchedTV = true;
		break;

	case 2:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You turned on the TV.");
		TelevisionImage(true);
		ui->PrintDialogue(Vector2(POINTX, POINTY), "TV: BREAKING NEWS, A SERIAL KILLER IS ON THE LOOSE AROUND KRANJI ROAD, PLEASE CHECK YOUR LOCKS AND KEEP YOURSELF SAFE!");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: It's the same news...again...");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You realized that you are stuck in a time loop of getting killed over and over.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I have to do something about this...");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You turned off the TV.");
		TelevisionImage();
		break;
	default:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You turned on the TV.");
		TelevisionImage(true);
		ui->PrintDialogue(Vector2(POINTX, POINTY), "TV: BREAKING NEWS, A SERIAL KILLER IS ON THE LOOSE AROUND KRANJI ROAD, PLEASE CHECK YOUR LOCKS AND KEEP YOURSELF SAFE!");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You turned off the TV.");
		TelevisionImage();
		*hasWatchedTV = true;
		break;
	}
	Sleep(500);
}

void InteractionsManager::MainDoorInteracted(GameObject* MainDoor, GameObject* player)
{
	Start();
	MainDoorImage();
	ui->CreateOptionUI(Vector2(POINTX, 13), false);
	switch (timeSystem->TimeLoop)
	{
	case 0:
	case 1:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Strange... I can't open the door.");
		break;
	default:
		if (!isDoorBarricaded)
		{
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Strange, the door can't be opened");
		}
		else
		{
			BarricadeDoorImage();
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I have barricaded the door.");
		}
		
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

void InteractionsManager::ToiletBowlInteracted(GameObject* ToiletBowl, GameObject* player)
{
	ToiletBowlImage();
	ui->PrintDialogue(Vector2(POINTX, POINTY), "Just a toilet bowl, nothing else.");
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

	if (isStoreRoomUnlocked)
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
	ClockImage();
	switch (timeSystem->TimeLoop)
	{
	case 0:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "It's quite late.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "I should really go to bed now.");
		break;

	default:
		timeSystem->increaseTimeTaken(2);
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: I remember that he comes at 00:05, I still have time.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "The time is currently: " +
			GameManager::getGM()->TimeSys.GetTimeinString(GameManager::getGM()->TimeSys.TimeTaken));
		break;

	}
	
}

bool InteractionsManager::UseItem(std::string useItem, GameObject* player)
{
	UI ui(Vector2(Application::numberOfColumns / 2 - 171 / 2, 35), 0, 166);

	std::string keyword;
	std::string useItem1; 
	std::string useItem2; 
	std::string useItem3; 
	std::string keyword2;
	std::string onObject; 
	SeperateInput(useItem, useItem1, keyword);
	SeperateInput(keyword, keyword, useItem2);
	if (!GameManager::getGM()->inventory.InventoryHasItems(useItem1))
	{
		GameManager::getGM()->ClearDialogue();
		ui.PrintDialogue(Vector2(3,2), "No " + useItem1 + " in Inventory");
		return false;
	}
	if ((keyword != "with" && keyword != "and") && keyword.length() > 0)
	{

		if (keyword != "on")
		{
			GameManager::getGM()->ClearDialogue();
			ui.PrintDialogue(Vector2(3, 2), "Invalid Input");
			return false;
		}
		else
		{
			keyword2 = keyword;

			SeperateInput(useItem2, onObject, useItem2); 
		}
	}
	else if (keyword == "with" || keyword == "and")
	{
		SeperateInput(useItem2, useItem2, keyword); 
		SeperateInput(keyword, keyword, useItem3); 
		if (!GameManager::getGM()->inventory.InventoryHasItems(useItem2) ) 
		{

			GameManager::getGM()->ClearDialogue(); 
			ui.PrintDialogue(Vector2(2,2), "No " + useItem2 + " in Inventory");
			return false;
		}
		if ((keyword != "with" && keyword != "and") && keyword.length() > 0)
		{
			SeperateInput(useItem3, useItem3, keyword);
			SeperateInput(keyword, keyword, onObject);
			if (keyword != "on")
			{
				GameManager::getGM()->ClearDialogue();
				ui.PrintDialogue(Vector2(3, 2), "Invalid Input");
				return false;
			}
			else
			{
				keyword2 = keyword;

				SeperateInput(useItem3, onObject, useItem3); 
			}
		}
		else if (keyword == "with" || keyword == "and")
		{

			SeperateInput(useItem3, useItem3, keyword2);
			

			if (!GameManager::getGM()->inventory.InventoryHasItems(useItem3)) 
			{
				GameManager::getGM()->ClearDialogue();
				ui.PrintDialogue(Vector2(2,2), "No " + useItem3 + " in Inventory");
				return false;
			}

			if (keyword2.length() > 0)
			{
				SeperateInput(keyword2, keyword2, onObject);
				if (keyword2 != "on")
				{
					GameManager::getGM()->ClearDialogue();
					ui.PrintDialogue(Vector2(3, 2), "Invalid Input");
					return false;
				}
			}
		}

	}



	Furniture* furnituresLeft, * furnituresRight, * furnituresUp, * furnituresDown;
	furnituresLeft = dynamic_cast<Furniture*>(SceneManager::currentScene->GetObjectManager()->GetObjectAtPosition(Vector2(player->GetPosition()->GetX() - 1, player->GetPosition()->GetY())));
	furnituresRight = dynamic_cast<Furniture*>(SceneManager::currentScene->GetObjectManager()->GetObjectAtPosition(Vector2(player->GetPosition()->GetX() + 1, player->GetPosition()->GetY())));
	furnituresUp = dynamic_cast<Furniture*>(SceneManager::currentScene->GetObjectManager()->GetObjectAtPosition(Vector2(player->GetPosition()->GetX(), player->GetPosition()->GetY() - 1)));
	furnituresDown = dynamic_cast<Furniture*>(SceneManager::currentScene->GetObjectManager()->GetObjectAtPosition(Vector2(player->GetPosition()->GetX(), player->GetPosition()->GetY() + 1)));
	GameManager::getGM()->ClearDialogue();
	ui.CreateText("Use item(s) on what? Enter 'on <Object Name>'", Vector2(3, 2)); 
	GameManager::getGM()->DisplayFurnituresAroundPlayer(Vector2(2, 3)); //print at (2,3);
	std::string input = "";
	if (keyword2.length() > 0)
		input = keyword2 + " " + onObject;
	else
		input = GameManager::getGM()->InputField();
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
				ui.PrintDialogue(Vector2(3, 2), "Using Nails, Planks and Hammer on the main door.");
				ui.PrintDialogue(Vector2(3,2), "You: I could barricade the door, this can buy some time.");
				timeSystem->increaseTimeTaken(50);
				isBarricadeSetup = true;
				ui.PrintDialogue(Vector2(3,2), "You: There, all good.");
				BarricadeDoorImage();
				ui.PrintDialogue(Vector2(3,2), "Successfully barricaded the door!");
				GameManager::getGM()->inventory.UseItem(useItem1);
				GameManager::getGM()->inventory.UseItem(useItem2);
				GameManager::getGM()->inventory.UseItem(useItem3);
			}
			else 
			{
				GameManager::getGM()->ClearDialogue();
				ui.PrintDialogue(Vector2(3,2), "I dont have enough items to use on the main door! Maybe i need nails, planks or hammer?");
			}
			return true;
		}

		if (furnituresRight->GetFurnitureType() == Furniture::Closet && (input == "on closet"))
		{
			bool usingUnknownKey = useItem1 == "unknownkey";

			if (usingUnknownKey)
			{
				GameManager::getGM()->ClearDialogue();
				ui.PrintDialogue(Vector2(3, 2), "Using Unknown Key to unlock Closet.");
				isClosetUnlocked = true;
				ui.PrintDialogue(Vector2(3, 2), "Successfully unlocked the closet!");
				GameManager::getGM()->inventory.UseItem(useItem1);
			}
			else
			{
				GameManager::getGM()->ClearDialogue();
				ui.PrintDialogue(Vector2(3, 2), "You: I dont have a key to unlock this.");
			}
			return true;
		}
	}
	if (furnituresLeft)
	{
		if (furnituresLeft->GetFurnitureType() == Furniture::StoreRoomDoor && (input == "on door" || input == "on storeroom door" || input == "on store room door") || input == "on storeroom")
		{
			bool usingStoreroomKey = useItem1 == "storeroomkey";

			if (usingStoreroomKey)
			{
				GameManager::getGM()->ClearDialogue();
				ui.PrintDialogue(Vector2(3, 2), "Using Storeroom Key to unlock Storeroom.");
				isStoreRoomUnlocked = true;
				ui.PrintDialogue(Vector2(3, 2), "Successfully unlocked the door!");
				GameManager::getGM()->inventory.UseItem(useItem1);
			}
			else
			{
				GameManager::getGM()->ClearDialogue();
				ui.PrintDialogue(Vector2(3, 2), "You: I dont have a key to unlock this.");
			}
			return true;
		}
	}
	if (furnituresUp)
	{
		if (furnituresUp->GetFurnitureType() == Furniture::Closet && (input == "on closet"))
		{
			bool usingUnknownKey = useItem1 == "unknownkey";

			if (usingUnknownKey)
			{
				GameManager::getGM()->ClearDialogue();
				ui.PrintDialogue(Vector2(3, 2), "Using Unknown Key to unlock Closet.");
				isClosetUnlocked = true;
				ui.PrintDialogue(Vector2(3, 2), "Successfully unlocked the closet!");
				GameManager::getGM()->inventory.UseItem(useItem1);
			}
			else
			{
				GameManager::getGM()->ClearDialogue();
				ui.PrintDialogue(Vector2(3, 2), "You: I dont have a key to unlock this.");
			}
			return true;
		}
	}
	if (input == "on floor")
	{
		bool usingShampoo = useItem1 == "soap";

		if (usingShampoo)
		{
			GameManager::getGM()->ClearDialogue();
			ui.PrintDialogue(Vector2(3, 2), "Using soap on floor!");
			ui.PrintDialogue(Vector2(3, 2), "You: I can make the floor slippery so it buys time.");
			timeSystem->increaseTimeTaken(45);
			isSoapSetup = true;
			ui.PrintDialogue(Vector2(3, 2), "You: There, all good.");
			ui.PrintDialogue(Vector2(3, 2), "Successfully used soap on floor!");
			GameManager::getGM()->inventory.UseItem(useItem1);
		}
		else
		{
			GameManager::getGM()->ClearDialogue();
			ui.PrintDialogue(Vector2(3, 2), "I dont have enough items to use on the floor!");
		}
		return true;
	}

	if (input == "on you")
	{
		bool usingKnife = useItem1 == "knife";

		if (usingKnife)
		{
			GameManager::getGM()->ClearDialogue();
			KnifeImage();
			ui.PrintDialogue(Vector2(3, 2), "This better work...");
			isPlayerSucide = true;
			GameManager::getGM()->inventory.UseItem(useItem1);
		}
		else
		{
			GameManager::getGM()->ClearDialogue();
			ui.PrintDialogue(Vector2(3, 2), "I dont think i can use that on myself...");
		}
		return true;
	}
	return false;
}


void InteractionsManager::ToiletCabinetInteracted(GameObject* toiletCabinet, GameObject* player)
{
	Start();
	ui->CreateOptionUI(Vector2(POINTX, POINTY), false);
		timeSystem->increaseTimeTaken(5);
		ui->GetOptionUI()->AddOption(new std::string("Yes"));
		ui->GetOptionUI()->AddOption(new std::string("No"));
		ToiletCabinetImage();
		int choosenItem = ui->PickDialogue(Vector2(POINTX, POINTY), "Search the cabinet?");
		switch (choosenItem)
		{
		case 0:
			ToiletCabinetImage(true);
			timeSystem->increaseTimeTaken(5);
			ui->PrintDialogue(Vector2(POINTX, POINTY), "You look through the cabinet!");
			ui->PrintDialogue(Vector2(POINTX, POINTY), "But you found nothing useful.");
			break;
		case 1:
			break;
		}
	
}

void InteractionsManager::FridgeInteracted(GameObject* fridge, GameObject* player)
{
	
	ui->PrintDialogue(Vector2(POINTX, POINTY), "There's nothing in the fridge.");
}

void InteractionsManager::KitchenTableInteracted(GameObject* table, GameObject* player)
{
	ui->PrintDialogue(Vector2(POINTX, POINTY), "There's nothing on the table.");
}

void InteractionsManager::Start()
{
	ui = GameManager::getGM()->gameUI;
	timeSystem = &GameManager::getGM()->TimeSys;
	
}

void InteractionsManager::Start(bool isGameStarted)
{
	ObjectivesManager* objManager = &(GameManager::getGM()->objManager);
	Start();
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
		ui->PrintDialogue(Vector2(POINTX, POINTY), "I still remember the dream, it felt like I got stabbed.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "I can still feel it till now...it felt too real...");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "Whatever, I don't want to think too much.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "Strange, I don't feel tired though...so I don't think I can sleep.");
		break;
	case 2:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You appear at the door again");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: WHAT WAS THAT!? I JUST GOT KILLED IN MY HOUSE!");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You quickly calm down and decide to check the TV.");
		break;
	default:
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Im back again...");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: Whatever I did last time didn't work.");
		ui->PrintDialogue(Vector2(POINTX, POINTY), "You: There has to be a way out of this.");
		break;
	}
}

void InteractionsManager::MainDoorImage()
{
	const char* image = R"(@@&#####################&##########################################################&#######################&@@
@G:                       .^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^.                         :G@
@G:                       J@&GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG&@Y                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                           .::.   ?@5                         :G@
@G:                       J@J                                         .!P##P~. ?@5                         :G@
@G:                       J@J                                        :#@^  ~@B.7@5                         :G@
@G:                       J@J                                        .?5JJJY5! ?@5                         :G@
@G:                       J@J                                           7YY7   ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@@&#######################&@&##################################################&@&#########################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);

}

void InteractionsManager::SofaImage()
{
	const char* image = R"(@@&############################################&@@@@@&####&@@@&##################&#####@@@@@@@@@@@@@&######&@@
@G:                                        .^^^JBBGBP:    ~G#BY^^^.                .^^~5#BBBBBBBBBBBJ^^^^: .G@
@G:                                   ~7777JGBGJ!!!!!7!       ~G@@?              :75GBP^            !GGG@@Y?B@
@G:                               7J?P@@P5P!   !5P55555Y7       ~Y5?:        :7JJ55~                    !55P&@
@G:                         ~Y5555YJJJJ!              .7Y5557     ~J5J:    .?B@&J:                         .G@
@G:                     ~PGP&@5~!~                       ~P@G       G@&Y..J#@B!7PGGGGGGGGGGBY.             :G@
@G:                 ^P#B&@@@@@#BGB#P:                      :JBJ     :^^!P&@@@@BY~^~~~~~~~~~^7G#BBBBB#B7    :G@
@G:               ^G@@G^.....:::.~G@@P:                     7&@&?    .5&@B~ .::.             :::::.:Y@@#&B~:G@
@G:      .:::.^P&@P^               ^BB~                       J@Y:5@@B~                                ^P@@@@@
@G:    .~P@&B#G~                     ~&B:                    ^5@@BBG~                               .^Y#&@@@@@
@G. ~!7JG@@5^                        ~@B.                   7@@PJ!!!7777777777777^              .!!!G@? Y@BG&@
@#J5@@P~ ^Y@@B?.                     :JYJ~              .?YJYY~ ~5P55555555555555YJJJJJY?.    .?G@@@#Y: P@~ G@
@@@&J^     ^?JJ5J:                     !@G.          7555JJJ!                    ^JYJJJJJ55YYYYJJ???: ~5Y7.:G@
@#?:          .#@~                     !&G.        J#@@Y^                                ^J&@@G.    !PY!.  :G@
@G:            .!GP:                   !&G.  7B#B#G?^^:                                 .5G!^^:   !B@@?    :G@
@G:             :G@@P:                 !&P.7#Y:.:::                                 .Y&@B!.     7#5:...    :G@
@G:               ~&#~              ...7B@&Y^.:::::::::::::::::::::.             ?@@#7        7#5.         :G@
@G:               ^P&@P.           :#@&Y.  !B#BBBBBBBBBBBBBBBBBBBB@@Y^         .^YB7       :J@B:           :G@
@G:                 ~&G.        ~77?PY.                           7GBPJ~   .!77YG7     ~77?PGGJ.           :G@
@G:                 !&G.      ~Y55PJ.                                 ?5J?JY5PP7     ~Y55PJ.               :G@
@G:                 !&G.  ~Y5YJ7.                                      .#@P!     ~Y555?:                   :G@
@G:                 !@G :P&@@@#PGP^                                 ?BBP?^     ~P@@G!.                     :G@
@G:                  :7G@@P^:^^~^!P##BBBBBBBB#B7                  JBJ^~^     ~G@@P^                        :G@
@@@5:             ^G&#&@P^        .::::::::::.:Y&&#&G~          J#J.       ~B@@P:                          :G@
@@&###############&@P.~B@#J:                    ..  :P&&P^   .J#J        !G@@5.                            :G@
@G:                       ?BY^^^                        ~&#!?BJ     :~^!GP:                                :G@
@G:                         7G@@5~.                  ~77?5GB?   :!!75GB5:                                  :G@
@G:                           ~5@@~              !JJJ5PP?.  .??J#@&Y^                                      :G@
@G:                             ~JYJ:        ~5P5YJY?.    :Y#@#J??:                                        :G@
@G:                              .B&^    ~PBGY77!.    .YGG57!!:                                            :G@
@G:                              :G@#BBBB5~^^.   J#BBB#@#!.                                                :G@
@@&##############################&@@@@@@@@######&@@@@@@@@###&##############################################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);

}

void InteractionsManager::TableImage()
{
	const char* image = R"(@@&##################################&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@G:                                  ^#@GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG&@
@G:                                .^J&@BGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGB&@
@G:                                :#@&BGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGB&@
@G:                               7PB#GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGB&@
@G:                           7GGG##GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGB&@
@G:                         ?B@@&BGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGB&@
@G:                         Y@&GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGB&@
@G:                      .J&#GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGB&@
@G:                    :J&&GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGB&@
@G:                   !@@GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGB&@
@G:                 :75##GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGB&@
@G:                 ~@@GPGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGB&@
@G:               :YBBBGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGB&@
@G:             :5##BGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGB&@
@G:           .P&#GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGB&@
@G:           .G@BGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGB&@
@G:          .!G@BGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGB&@
@G:        :7G@BGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGB&@
@G:      ^?#@#PGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGB&@
@G:      Y@@BGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGB&@
@G:      J@@&&#BGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGPG&@
@G:      Y@Y^P@@@@@@@@@@@@#GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG#@@&@@@@
@G:      Y@7 P@?.:::::::.:J@@&&&&&&&&&&&&&&#GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG#@@&@&?:P&7^G@
@G:      Y@7 5@&##########@@Y::::::::::::::J@@@@@@@&############################################&&Y^.:Y&@&~.G@
@G:      Y@7 P&!          7B#BBBBBBBBBBBBBBBBBBBB@@J^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^JB&B! 5&~.G@
@G:      Y@7 P&!                                 ?GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG?    .P&~.G@
@G:      Y@7 P&!                                                                                       .P&~.G@
@G:      Y@7 P&!                                                                                       .P&~.G@
@G:      Y@7 P&!                                                                                       .P&~.G@
@G:      Y@7 P&!                                                                                        P&~.G@
@@&######&@&&@@&#######################################################################################&@@&&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);

}

void InteractionsManager::SinkImage()
{
	const char* image = R"(@@&########################################################################################################&@@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                 J##BB##5.                              :G@
@G^                                .                             .5#?..:::.!#P.            .               :G@
@@###########@#7..:::::::::......^P&#########&@&################&@@#!  ~##~  7&@###########&P~.:::.        :G@
@G:      .^:~G@@@#BBBBBBBB&@@@@@@&?.         Y@5:               Y@?  .G@##@G.!@P            ^P#B##Y^.      :G@
@G:      J@&GPPGY:        !PGPPPPG@@J!77!^   !P@@?              Y@P!~?&&^.5Y.^P?                  J@5      :G@
@G:    ^?#@?                      75555B@G.    5@?              ~JYYYYY?.                         J@Y      :G@
@G:    J@B?:                           ~&G.    5@?  .?5555555555YYYYYYJYY5555555555555555555557   ^?YY~    :G@
@G:    J@J                           :Y#@P.    5@?  :B@BPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPB@@G?.  Y@J    :G@
@G:    ?@@BBBBBB##P:        ?##BBBBBB#@@@P.    5@?  :B@Y?????????????????????????????????????JG@P.  Y@J    :G@
@G:    J@5::::::::!G&#####&#J:::::::.7&B^      5@7 Y@@#Y??JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ??5&@&J  :5#7  :G@
@G:    7#@@&######P~::::::::J#####B#@@@5.    Y@J  .G@5??JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ??JP&Y   5@?  :G@
@G:      ?BJ^^^^^^!PBBBBBBBBJ^^^^^^!GP:      Y@J  .G@5??JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ?JJG@P.  .^G@?  :G@
@G:        ?GGGGGGP7~!!!!!!!YGGGGGB5:        J@J  .G@5??JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ??5@@G?.  J@@&7  :G@
@G:               .JP55555P5~              :?B@J  .G@5??JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ??JPP57   ^?G@@@!  :G@
@G.                                        J@#?^  .G@#PJ??JJJJJJJJJJJJJJJJJJJJJJJJJJJJJ?JP#@#:    ?@@BBBPJ.:G@
@&GPPPPPPGP~                       .YGPPPGGY!:     ^?&@@GJ???????????JJJJJJJJJJ???????JG&@@J^.  ~5#@B5YP@@~.G@
@&BGGGGGGGGBBBBBBBBBBBBBBBBBBBBBBBB#@@@@@G~.         :^^7B@&&&&&&&&#5??????????5&&&&&@#?^^:     7@@@B55P&&~.G@
@&P55555555PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPG#######&B!     :::::::.:5@@&&&&&&&&&&5:.:::::       !B#PB@#55P&&~.G@
@&P5PPPPPPPP55555555555555555555555555555B@#P5PPP5P#@&&&&&&&&&&&&&&@@@@#!.::::::...    .::..!B&P55B@#55P&&~.G@
@&P5PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP55B@#P5PPPPP55555555555555555555P#@&&&&&&&@@5^:~G@@&@#P55PPB&BP5P&&~.G@
@&P5PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP55B@#P5PPPPPPPPPPPPPPPPPPPPPPPPP5555555555G#&&&&&#P555555B@#55P5P&&~.G@
@&P5PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP55B@#P5PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP555555555PPPP55B@#P5P5P&&~.G@
@&P5PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP55B@#P5PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP55B@#P5P5P&&~.G@
@&P5PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP55B@#P5PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP55B@#P5P5P&&~.G@
@&P55555555555555555555555555555555555555B@#P555555555555555555555555555555555555555555555555555B@#P555P&&~.G@
@@@&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);

}

void InteractionsManager::PlanksImage()
{

	const char* image = R"(@@&####&@&############&@@&#############################################################################&&@@@@@
@G:    J@Y            7@P                                                                               5@#B&@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P               ^^^^^^^^^^^^^^^^^^^^^^.                                        .P&~.G@
@G:    J@Y            !@#7!7777777777!~Y@@##################@@G7!!!!!!!!!!!!!!!!!7!:                   .P&~.G@
@G:    J@Y          :7JY555555555555YP@@BY7!!!!!!!!!!!!!!!!!JPBBBBBBBBBBBBBBBBBGB@@B??JJ7.              P&~ G@
@G:    J@Y          !@B             7P@B7~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!J5PPPG@@PY5555555555555&@GP#@
@G:    J@Y      .JGG57^            :#@@&#BBBBBBBBBBBBBBBBBBBBB#BY!!777777777777777777!!?5@@J!77777777777!!!?#@
@G:    J@Y    .Y&@&7:            :5BPPPPPPPPPPPPPPPPPPPPPPPPPP#@@############&#P7!7!7P###@B^               :G@
@G:    J@Y  .5#7...              :G@@&&&&@@B5Y5555555YYYYYYYYY555555555555555G@@&&&&&@@GP&#~               :G@
@G:    J@Y:Y#7                     ^B@BGG#@@@&@@@@@@&P5555555555555555555555555PPPPPPP5555G@G:             :G@
@G:    ?@@@7                       ^B@#B###########B#@@@&&&&&&&&&&&&&@@@@@@@@@@@@@@@@@@@@&@@B!.            :G@
@G:    ?@@@P!!77777777~            .JPPPPPPPPPPPPPPPG@@&############BGGGGGGGGGGGGGGGGGGGGGG#@@G.           :G@
@G:    ?@BYY5555555555Y??JJJJJJJJJJJ??J~             7YJJJJJYYYYYYY5B&&&&&&&&&&&&&&&&&&&&&&&@@&Y~          :G@
@G:    J@J            !@&J?JJJJJJJJJJJJY5555555555555YYYYY55!       ^?77777777777?????????????JJ!          :G@
@G:    J@Y            7@5              .!7777777777777777777JGGGGGGGPPPPPPPPPPPGP!                         :G@
@G:    J@Y            7@P.                                  .~~~~~~~~~~~~~~~~~~^^JB#BBBBBBBBBBBBBBBBBBBBBBB#&@
@G:    J@Y            7@P.                                                       .::::::::::::::::::::.^G@7^G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P                                                                               P&~.G@
@@&####&@&############&@@&#############################################################################&@@&&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::PlanksImage(bool)
{
	const char* image = R"(@@&####&@&############&@@&#############################################################################&&@@@@@
@G:    J@Y            7@P                                                                               5@#B&@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P                                                                              .P&~.G@
@G:    J@Y            !@#7!7777777777777!^                                                             .P&~.G@
@G:    J@Y          :7JY555555555555555B@&Y?JJJJJJJJJJJY7                                               P&~ G@
@G:    J@Y          !@B                .7JJJJJJJJJJJJJJJY55555555555555555555555555555555555555555555555&@GP#@
@G:    J@Y      .JGG57^                                 .!7777777777777777777777777777777777777777777777!!!?#@
@G:    J@Y    .Y&@&7:                                                                                      :G@
@G:    J@Y  .5#7...                                                                                        :G@
@G:    J@Y:Y#7                                                                                             :G@
@G:    ?@@@7                                                                                               :G@
@G:    ?@@@P!!77777777~                                                                                    :G@
@G:    ?@BYY5555555555Y??JJJJJJJJJJJJJY!                                                                   :G@
@G:    J@J            !@&J?JJJJJJJJJJJJY555555555555555555PP7                                              :G@
@G:    J@Y            7@5              .!7777777777777777777JGGGGGGGGGGGGGGGGGGBG7                         :G@
@G:    J@Y            7@P.                                  .~~~~~~~~~~~~~~~~~~^^JB#BBBBBBBBBBBBBBBBBBBBBBB#&@
@G:    J@Y            7@P.                                                       .::::::::::::::::::::.^G@7^G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P.                                                                             .P&~.G@
@G:    J@Y            7@P                                                                               P&~.G@
@@&####&@&############&@@&#############################################################################&@@&&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::ToolboxImage()
{
	const char* image = R"(@@&######################################&@@&###&&@@@@@@@@@@@@@@&##############&######&@@&##&##############&@@
@G:                                      7@5     5@@&&&&&&&&&&@&Y^:^^^^^^^^^^:        .G@?.                :G@
@G:                                    .~5@P     5@B55PPPPPPPP55B&@&&&&&&&&@@G7:      .?B@#^               :G@
@G:                                    ~@@5!   ^?G#GPPPPPPPPPPPPP555555555555B@#?^      .B@5!.             :G@
@G:                                  :?B@P     Y@#55PPPPPPPPPPPPPPPPPPPPPPPPPPB@@Y      .~5@#^             :G@
@G:                                  ~&&?:   !P&@BPPPPPPPPPPPPPPPPPPPPPPPPPPP55B@Y        :##^             :G@
@G:                                  ~&G.    J@&GPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP#@Y        ^##^             :G@
@G:                                  ~#G:  ?##PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP#&?      ^##^             :G@
@G:                                ^#B^  7&@@BP5PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP5P#@J      ~BG:             :G@
@G:                                ^##^  7&&P5PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP#@J    :B&^               :G@
@G:                                ^#B:  7@@BBBBBBBBBBGP55555555PPPPPPPPPPPPPPPPP#@J    :B#~               :G@
@G:                                :B&Y~ :?YJJJJJJJJ5&@&########G555555PPPPPPPPPP#@J    .B#~               :G@
@G:                               7P&@@@PYYYYYYYYYYJ5@@J!777????P&&&&&&#P5555PPPP#@J  .!P@&~               :G@
@G:                           7GGB@@@B?!?????????????7?5PPPG7   .~!~!!~?B@@&&BP55#@J  .G@Y^.               :G@
@G:                         7B@@Y~^7#@#Y: ............:~!!!!JB#BBBBG~   :^:?&@@&&@@J  .G&~                 :G@
@G:                       ?&@@J:....:?&B^.:::::::::::::.....:^~^^~P@@#####&P^.:::::  5#?.                  :G@
@G:                    .?#@&J:..::.. !&B^ ....:::::::::::::::.....::::::.!B@###&@@@7 5@7                   :G@
@G:                  :Y@G: ..:::..^~~J@#7~!!!^.............:::::::::::::::.....7B@@Y~5G!                   :G@
@G:                 ~@@B?:.:.. .~J&@#GGGGGGBG5?7??????????!. ..........::::::::  J@&P~                     :G@
@G:             .!JJY5?. :..~JYYPGPJ^^?YYYYYJ5GGGPPPPPGGGGPYJYYYYYYYYJ^  ......~?B@P!:                     :G@
@G:             :B@P7: :..~5&@BJ~^?PPB@&Y??G@P^:^JPPY~::::!Y5YYY5555555PPPPPP?.?@@@@@?                     :G@
@G:           .?B@#~ .. !P@@G?YGG#@@J!!^   ?@P~:^!Y&@#BBBBY^7GBG?^^^^~?YJJJJJYP#@@@5~.                     :G@
@G:           .B@J^:..!G@@G7^^G@Y^^:       ?@5~Y#&BJ!777Y@B!^7G@P^^^~~^^^^^^:J@G^Y@J                       :G@
@G:        Y&&&@B! ...?@B!^~5#?.         !B@@5~~!!7GB!!G@@B!^~~!~~P&J^^~~^^?#P^  J@J                       :G@
@G:        J&@&?:.. 7&B!:^5@J     .::::::  7#&#@@Y!!7!~^7B@&&&5~^!B@Y^^^~J&B^  ?@5                         :G@
@G:         .5@@&J~^J&B~:^5@5^:^:!#@&##&@G~    7BBBB#@&J!~^^^^^~P@@B?^~J&@&Y.  ?@5                         :G@
@G:         .P@BPPB@@@#Y?JG@@@@@#GG5~.:!5&@B7!7!!!^  P@@#7^~~~^~JP7:!Y&@#J.  .~P@5                         :G@
@G:         .G@~  .?5YY5555YYYYYYYYY5555YY55PPPPP@@5J#@GY!^~^^^^7JYP@@B?   .!G@@5~                         :G@
@G:          ~J5J.              ~???????7JPPPPPPP&@@@@#!.^^^7PGG@@G??!  755B@&J^                           :G@
@G:           .B@#PGGGGGGGGGGGGGPPPPPPPPPY!~!!!!!~~~~^7PBGBBY!~!!~  7PPB@@J!!^                             :G@
@G:            :^^^^^^^^^^^^^^^^^^^^^^^^^?GBGGGGGGGGGGB@@@@@&GGGGGGB@@?^^:                                 :G@
@@&##########&###########################&@@@@@@@@@@@@@@@@@@@@@@@@@@@@&####&###############################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::ToolboxImage(bool)
{
	const char* image = R"(@@&######################################&@@&###&&@@@@@@@@@@@@@@&##############&######&@@&##&##############&@@
@G:                                      7@5     5@@&&&&&&&&&&@&Y^:^^^^^^^^^^:        .G@?.                :G@
@G:                                    .~5@P     5@B55PPPPPPPP55B&@&&&&&&&&@@G7:      .?B@#^               :G@
@G:                                    ~@@5!   ^?G#GPPPPPPPPPPPPP555555555555B@#?^      .B@5!.             :G@
@G:                                  :?B@P     Y@#55PPPPPPPPPPPPPPPPPPPPPPPPPPB@@Y      .~5@#^             :G@
@G:                                  ~&&?:   !P&@BPPPPPPPPPPPPPPPPPPPPPPPPPPP55B@Y        :##^             :G@
@G:                                  ~&G.    J@&GPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP#@Y        ^##^             :G@
@G:                                  ~#G:  ?##PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP#&?      ^##^             :G@
@G:                                ^#B^  7&@@BP5PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP5P#@J      ~BG:             :G@
@G:                                ^##^  7&&P5PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP#@J    :B&^               :G@
@G:                                ^#B:  7@@BBBBBBBBBBGP55555555PPPPPPPPPPPPPPPPP#@J    :B#~               :G@
@G:                                :B&Y~ :?YJJJJJJJJ5&@&########G555555PPPPPPPPPP#@J    .B#~               :G@
@G:                               7P&@@@PYYYYYYYYYYJ5@@J!777????P&&&&&&#P5555PPPP#@J  .!P@&~               :G@
@G:                           7GGB@@@B?!?????????????7?5PPPG7   .~!~!!~?B@@&&BP55#@J  .G@Y^.               :G@
@G:                         7B@@Y~^7#@#Y: ............:~!!!!JB#BBBBG~   :^:?&@@&&@@J  .G&~                 :G@
@G:                       ?&@@J:....:?&B^.:::::::::::::.....:^~^^~P@@#####&P^.:::::  5#?.                  :G@
@G:                    .?#@&J:..::.. !&B^ ....:::::::::::::::.....::::::.!B@###&@@@7 5@7                   :G@
@G:                  :Y@G: ..:::..^~~J@#7~!!!^.............:::::::::::::::.....7B@@Y~5G!                   :G@
@G:                 ~@@B?:.:.. .~J&@#GGGBBBBB5?7??????????!. ..........::::::::  J@&P~                     :G@
@G:             .!JJY5?. :..~JYYPGGY!:^^^^^^^?GGGGGGGGGGGGPYJYYYYYYYYJ^  ......~?B@P!:                     :G@
@G:             :B@P7: :..~5&@#Y!^^^~~~~~~~~~^^^^^^^^^^^^^!YP5555555555PPPPPP?.?@@@@@?                     :G@
@G:           .?B@#~ .. !P@@B?~^^~~~~~~~~~~~~~~~~~~~~~~~~~^^^^^^^^^^^~?YJJJJJYP#@@@5~.                     :G@
@G:           .B@J^:..!G@@G7~^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^^^:J@G^Y@J                       :G@
@G:        Y&&&@B! ...?@B!^^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^?#P^  J@J                       :G@
@G:        J&@&?:.. 7&B!^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^~J&B^  ?@5                         :G@
@G:         .5@@&J~^J&B~:^^^^^^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^~J&@&Y.  ?@5                         :G@
@G:         .P@BPPB@@@#YJJJJJJYJ!^^^^^^^^^~~~~~~~~~~~~~~~~~~~~~~^^^^!Y&@#J.  .~P@5                         :G@
@G:         .G@~  .?5YY55555555555555555PJ^:^^^^^^^^^^^~~~~~^^^^7YYP@@B?   .!G@@5~                         :G@
@G:          ~J5J.              ~???????7JPGGGGGGGGGGG5!:^^^7PGG@@G??!  755B@&J^                           :G@
@G:           .B@#PGGGGGGGGGGGGGPPPPPPPPPY!~!!!!!!!!!~7PBGBBY!~!!~  7PPB@@J!!^                             :G@
@G:            :^^^^^^^^^^^^^^^^^^^^^^^^^?GBGGGGGGGGGGB@@@@@&GGGGGGB@@?^^:                                 :G@
@@&##########&###########################&@@@@@@@@@@@@@@@@@@@@@@@@@@@@&####&###############################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::StoveImage()
{
	const char* image = R"(77777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
77777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
77777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
7777777777777777777777777777777777777777777777777777777777777777!777777777777777777777777777777777777777777777
GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGJ!!7777777777!777777777777777777777777777777
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#GBBGGGGGGGGGBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB#B57!77777777777777777777777777
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@BP555P#&&&&&&&&G5555555555555555PGGGGGGGGGGGGGGB############################
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@BP555G&@@G7!7!7P@@&@&G555555555PB&&&&&&&&&&#P5555B@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@B5555P&@@B!^~Y@@@5~^7G@@&P555555B@5~~!!!!77!~?#@@#P5P#@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&G5555P#@@#J!~JB&#Y~~~^!B@G555555#@G7!~^7B@@#7^^J&&G55B&@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@B5555555555P#&&BYJ?!^^~7JJY&@G555555G#@@Y^^!5BBP7^^J&@@#555#@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@&#G55555P55555555P#@@#5Y5&@@##BP5555PP55B@BY!^^^^^^!JG@@BG55PG#@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@&BP555P5555PB&#######&@&BB#BBP5555P55555P#@@@@#GGGGGG#@@@@BP55555GB&@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@&BGGP555P555B&&#5JJJJJJJJG@@#P555555555555G#@@P~^~!!!!!!!!~^~Y@@&&#G55P&@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@&P55555555B&@@57~~~~~~~~~~7G@@&G5555555555B@5^?GBGBBBBBBBBBBBJ^:^P@B55PPG&@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@&GP555555555#@5!~~~~~?B@@P!^~~7G@B5555555555B@J ?@@@?..::::..?@@&7 ?@@&G55P&@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@&G555555555555B@@&Y!~~^7B@&P!^~^~P@B5555555555B@5:  J&@#~      !B@@Y. ^P@#PPP5P&@@@@@@@@@@@@@@@@
@@@@@@@@@@@@#G5555555555555555B&@@57???77????7?G&B5555555555G&@@5^  P@J:       7@@@&BBBB#@@BGPG#&@@@@@@@@@@@@@
@@@@@@@@@@@#GGBBGP5555555555P555B&&&&&&&&&&&&&&G55555555555555G#@@5!?P@@Y!77777JP&@?    .JGPB@@B#@@@@@@@@@@@@@
@@@@@@@@@BPPGGGGGB########G555555555555555555555555555P555555555G#@@57?JYYYYY55~ 7@B???:    .J5YG@@@@@@@@@@@@@
@@@@@@@@@#5?~~~~!J55555555G#&######################&#P555555555555PB#B5JJJJJJJJJYPGB##BPY5?.    ~&@@@@@@@@@@@@
@@@@@@@@@@@5!~!~75BB5!^~~~?YYYYYYYYYYYYYYYYYYYYYYYYJ5B&&&&&&&&&&&&&&#&@@@@@@@@@@@@&#&#&@@@@GPPPP#@#YJYB@@@@@@@
@@@@@@@@@@@Y!5&#&@@@@##&P!~!!!!!!!!!!!!!!!!!!!!!!!!!!?JJ?????????????????????????????J???7Y&@@#Y??7!~!P@@@@@@@
@@@@@@@@@@@@#577777777775&&&&&&&&&&&&B?!!77777777777!!!!!!!!Y#&&#&&&&&&&&&&&#&&P7!!!!!7G&&&@@@&&&&P!~7P@@@@@@@
@@@@@@@@@@@@@Y~!!!!!!!!!!7777777777!!JB@&&&&&&&&&&&&&&&&&&&&&&P7!7777777777!!Y#@&&&&&&&@#J!!!!!777!!5@@@@@@@@@
@@@@@@@@@@@@@P?!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!7?G@@@@@@@@@
@@@@@@@@@@@@@@&Y~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!5@@@@@@@@@@@
@@@@@@@@@@@@@@&J~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~~Y@@@@@@@@@@@
@@@@@@@@@@@@@@@B57!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!?P#@@@@@@@@@@@
@@@@@@@@@@@@@@@@&J~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~Y@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@#J~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!JB&@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@#J~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~J&@@@@@@@@@@@@@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::StoveImage(bool)
{
	const char* image = R"(77777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
77777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
77777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777777
7777777777777777777777777777777777777777777777777777777777777777!777777777777777777777777777777777777777777777
GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGJ!!7777777777!777777777777777777777777777777
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#GBBGGGGGGGGGBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB#B57!77777777777777777777777777
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@BP555P#&&&&&&&&G5555555555555555PGGGGGGGGGGGGGGB############################
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@BP555G&@@G7!7!7P@@&@&G555555555PB&&&&&&&&&&#P5555B@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@B5555P&@@B!^~Y@@@5~^7G@@&P555555B@5~~!!!!77!~?#@@#P5P#@@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&G5555P#@@#J!~JB&#Y~~~^!B@G555555#@G7!~^7B@@#7^^J&&G55B&@@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@@@B5555555555P#&&BYJ?!^^~7JJY&@G555555G#@@Y^^!5BBP7^^J&@@#555#@@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@@@&#G55555P55555555P#@@#5Y5&@@##BP55555555#@BY7^^^^^^!YB@@#G55PG#@@@@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@@@@@&BP555P5555PB&#######&@&BB#BBP5555P5555555GB#BGPPPPPPGB#BG555P555GB&@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@&BGGP555P555B&&#5JJJJJJJJG@@#P55555555555555555555GBBGGBBG555555555P55P&@@@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@@@&P55555555B&@@57~~~~~~~~~~7G@@&G555555555555G&&&&&&&&&&&&&@#P555555555PPG&@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@&GP555555555#@5!~~~~~?B@@P!^~~7G@B555555555555#@P!!77777!!!!!Y&@&@@B555555P&@@@@@@@@@@@@@@@@@@
@@@@@@@@@@@@@@&G555555555555B@@&Y!~~^7B@&P!^~^~P@B555555555555#@5~^~~~~~!!!!~~!~~Y&@@B555555G&@@@@@@@@@@@@@@@@
@@@@@@@@@@@@#G5555555555555555B&@@57???77????7?G&B555555555555#@G7~~~~^7#@@B7^~~~^~P@B55555555G#@@@@@@@@@@@@@@
@@@@@@@@@@@#GGBBGP5555555555P555B&&&&&&&&&&&&&&G55555555555555G#@@G?!^^!5BG5!^~^~!JB@B5555555555G@@@@@@@@@@@@@
@@@@@@@@@BPPGGGGGB########G555555555555555555555555555P555555555G#@@BY55YYYY55555G##BG5555555555PB&@@@@@@@@@@@
@@@@@@@@@#5?~~~~!J55555555G#&######################&#P555555555555PBBBBBBBBBBBBBBG555555PB&#######&@@@@@@@@@@@
@@@@@@@@@@@5!~!~75BB5!^~~~?YYYYYYYYYYYYYYYYYYYYYYYYJ5B&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&#PJJJJJYYYYYJYB@@@@@@@
@@@@@@@@@@@Y!5&#&@@@@##&P!~!!!!!!!!!!!!!!!!!!!!!!!!!!?JJ???????????????????????????????J?!7G##P!~~!!~!P@@@@@@@
@@@@@@@@@@@@#577777777775&&&&&&&&&&&&B?!!77777777777!!!!!!!!Y#&&#&&&&&&&&&&&#&&P7!!!!!7G&&&@@@@&&&P!~7P@@@@@@@
@@@@@@@@@@@@@Y~!!!!!!!!!!7777777777!!JB@&&&&&&&&&&&&&&&&&&&&&&P7!7777777777!!Y#@&&&&&&&@#J!!!!!777!!5@@@@@@@@@
@@@@@@@@@@@@@P?!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!7?G@@@@@@@@@
@@@@@@@@@@@@@@&Y~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!5@@@@@@@@@@@
@@@@@@@@@@@@@@&J~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~~Y@@@@@@@@@@@
@@@@@@@@@@@@@@@B57!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!?P#@@@@@@@@@@@
@@@@@@@@@@@@@@@@&J~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~Y@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@#J~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!JB&@@@@@@@@@@@@@
@@@@@@@@@@@@@@@@#J~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~J&@@@@@@@@@@@@@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::KitchenCabinetImage()
{
	const char* image = R"(@@@@@@@@@@@&##########################################&########################################&######&####&@@
@&BBBBBBB#B?^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                            ^^^.      :G@
@G:        ?GGG&@@@@@#BB############################BJ!!!!!!!!!7777777777777777777777777777777!!5@@@Y      :G@
@G:           .P@BB@&P55J!!!!7777777777777777777777!?PBBBBBB&@#555555555555555555555555555555555YYB@Y      :G@
@G:           :G&J75PPB@@BBGY7!7777777777777777777777!!!!!!!5@Y                                   ?@Y      :G@
@G:           :G@Y7777?Y5555G##BBBBBBBBBBBBBBBBBBBBBBBBBBBBB&@5                                   J@Y      :G@
@G:           :G@Y7777777777?YJY#@GY555555555555555555555YG@G~.                                   J@Y      :G@
@G:           :G@Y777777777777!?B@5??JJJJJJJJJJJJJJJJJJJ??P@5                                     ?@Y      :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJJJJ??P@P.                                      Y@J    :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJJJJJYPBJ.                                      Y@J    :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJJJ?5@G.                                        Y@J    :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJJJ?5@G.                                        Y@J    :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJJJ?5@G.  !Y!                                   Y@J    :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJJ??5@G.  J@Y                                   :!YP~  :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJ?YB@@P.  J@Y                                     5@?  :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJ?5@B~  !#@@J                                     5@?  :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJYYYYYJP@B:  ?@5                                       5@?  :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJ?JB@&BBGB#@G:  ?@5                                       5@?  :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJ?J#@! :^ .B&?: 7@5                                       5@?  :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJ?JB@5?#@5Y#@@P.7@#?^                                     5@?  :G@
@G:           :G@Y7777777777777?B@5????????????G@@@@@5Y#@@P..7B@Y                                     5@?  :G@
@G:           :G@Y777777777777!?B@&############@@Y~~^ .B@@P.  ?@Y                                     5@?  :G@
@G:           :G@Y777777777777P&@&PJJYYYYYYYYJYB@#GGBB#@@@P.  J@Y                                     5@?  :G@
@G:           :G@Y777777777?P@@@P?7777777777777?JJJJJJJ?5@G.  ...                                     5@?  :G@
@G:           :G@Y77777777P@@&@@@@@@@@&################&@@P.                                          5@?  :G@
@G:           :G@Y777777?JG#57P&&##&@G:               :B@@P.                                        .^5B!  :G@
@#?!77!:      :G@Y77?Y55G#57777777!J&&?!!!!!!!!!!!!!!!?P&@P.                                        Y@J    :G@
@&PY5#@#J?JY?. G@Y!!Y@@GY!!7777777!?5GGGGGGGGGGGGGGGGBP7J@G.                                      :?B@J    :G@
@G.  :?JJJJJJYP&@#GG#@@BGBBBBBBBBBBBGGGGGGGGGGGGGGGGGGGG#@&P55555555555555555555555555555555555555#@#?^    :G@
@G:          ^7!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!7777777777777777777777777777777777777777!:      :G@
@G:                                                                                                        :G@
@@&########################################################################################################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::KitchenCabinetImage(bool)
{
	const char* image = R"(@@@@@@@@@@@&##########################################&########################################&######&####&@@
@&BBBBBBB#B?^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                            ^^^.      :G@
@G:        ?GGG&@@@@@#BB############################BJ!!!!!!!!!7777777777777777777777777777777!!5@@@Y      :G@
@G:           .P@BB@&P55J!!!!7777777777777777777777!?PBBBBBB&@#555555555555555555555555555555555YYB@Y      :G@
@G:           :G&J75PPB@@BBGY7!7777777777777777777777!!!!!!!5@Y                                   ?@Y      :G@
@G:           :G@Y7777?Y5555G##BBBBBBBBBBBBBBBBBBBBBBBBBBBBB&@5                                   J@Y      :G@
@G:           :G@Y7777777777?YJY#@GY555555555555555555555YG@G~.                                   J@Y      :G@
@G:           :G@Y777777777777!?B@5??JJJJJJJJJJJJJJJJJJJ??P@5                                     ?@Y      :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJJJJ??P@P.                                      Y@J    :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJJJJJYPBJ.                                      Y@J    :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJJJ?5@G.                                        Y@J    :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJJJ?5@G.                                        Y@J    :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJJJ?5@G.  !Y!                                   Y@J    :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJJ??5@G.  J@Y                                   :!YP~  :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJ?YB@@P.  J@Y                                     5@?  :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJ?5@B~  !#@@J                                     5@?  :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJYYYYYJP@B:  ?@5                                       5@?  :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJ?JB@&BBGB#@G:  ?@5                                       5@?  :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJ?J#@! :^ .B&?: 7@5                                       5@?  :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJ?JB@5?#@5Y#@@P.7@#?^                                     5@?  :G@
@G:           :G@Y7777777777777?B@5????????????G@@@@@5Y#@@P..7B@Y                                     5@?  :G@
@G:           :G@Y777777777777!?B@&############@@Y~~^ .B@@P.  ?@Y                                     5@?  :G@
@G:           :G@Y777777777777P&@&PJJYYYYYYYYJYB@#GGBB#@@@P.  J@Y                                     5@?  :G@
@G:           :G@Y777777777?P@@@5?7777777777777??JJJJJ??5@G.  ...                                     5@?  :G@
@G:           :G@Y77777777P@@&57777777777777777777777777Y@G.                                          5@?  :G@
@G:           :G@Y777777?JG#5777777777777777777777777777Y@G.                                        .^5B!  :G@
@#?!77!:      :G@Y77?Y55G#577777777777777777777777777777Y@G.                                        Y@J    :G@
@&PY5#@#J?JY?. G@Y!!Y@@GY!!777777777777777777777777777!!Y@P.                                      :?B@J    :G@
@G.  :?JJJJJJYP&@#GG#@@BGBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB#@&P55555555555555555555555555555555555555#@#?^    :G@
@G:          ^7!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!7777777777777777777777777777777777777777!:      :G@
@G:                                                                                                        :G@
@@&########################################################################################################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::TrashCanImage()
{
	const char* image = R"(@@&########################################################################################################&@@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                    ^PBGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGPGP7                         :G@
@G:                                  ^GG!^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^J@@@&B#B!                     :G@
@G:                            .5&&#&P~  !B&################################&5^ .J@@@?                     :G@
@G:                           5@@B!..!B&&&&P!~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~~Y@P:.:  P@7                   :G@
@G:                         .~5B!~B@@G!^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~?B&#&#J^YB?:                  :G@
@G:                       :!5G^ P@&P!^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~^~G@! G@!                 :G@
@G:                       Y@J ^JP5!^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~JPY?JYJ7.               :G@
@G:                       J@? 5@Y^^~~~~~~~~~~~~~^^^~~~~~~~~~~^^^^^~~~~~~~~~~~~~~~~~^~B@^ B@^               :G@
@G:                       J@? 5@Y^~~~~~~~~~~~~~YBBG7^~~~~~~^?GBGBGJ~~~~~~~~~~~~~~~~^!G@#577PY:             :G@
@G:                       J@? 5@Y^~~~~~~~~~~~:.Y@@@&G7^~~^?B@@@@@@5~^~~~~~~~~~~~~~~~~!?&&^.##^             :G@
@G:                       J@? 5@Y^~~~~~~~~~!~. Y@@@@&?^^?B@@G!5@P!^!P@&&&&&G7~~~~~~~~^!B&~:B#^             :G@
@G:                       J@? 5@Y^~~~~~~~J#@@@@&&&@@@##@@@@@G!J#@@Y7G@@@@#?J&B!^~~~~~~7#&^:B#^             :G@
@G:                       Y@? 5@Y^~~~~~~~^^Y@@@57G@@#!~P&@&G#@5^Y@#B&@@@@@@@&P?!~~~!?B@@&^:B#^             :G@
@G:                       7PJ!YPY?!~~!?JJ??G@@@@@BP#@@B.:&#!J&@@@@Y~P@@@@&BY^?@B!^~JB&@#Y.:##^             :G@
@G:                         5@7 G@J:^?@@@@@#5B@B?  5@@#Y7?P@@@@@PJB@@&5Y&&5JYG@G!^~7Y&@! ~J5?.             :G@
@G:                         5@7 ^JP5!!JG@@@#5B@GJJP#@@@@@Y5&@@@@PJG@@&5Y#@@@@&5?~^^P@G7 .B&^               :G@
@G:                         :!55:.B@?^^!?J?G@@@@@Y7G@@B!7&@@P~J@@@@@@@&#B#@&Y!^:^?G@@7 7B@#~               :G@
@G:                           P@!.P@&P!^~^^Y@@@@&~ 5@@&BB@@@#G#@Y^5@@@BG&#J!^?B##@@5^ .G@J:                :G@
@G:                            ^P#~^B@@G!^~~!5@@@GP#@@@@@@@@@@@@&#BB&@@#J~~~~Y@@@Y. .Y#7.                  :G@
@G:                            .P#7  ^G@@B7!!~~5&BP#&&#GG&#GPPB&&&&&&#?^~J#@&&&J  .Y#?                     :G@
@G:                              .5B7^^7PBB&@G?7???~^^^^^^^^^^!77777??7Y&@#J  :^^P@Y                       :G@
@G:                                .YBB57: ^5PPPPGP5JYYYYYYYJJB@@@@@BPPPPY!~!5@@GGP!                       :G@
@G:                                    :Y5J????J?. !5YYYYYYYYYJJJJJJ?77775@@P55!                           :G@
@G:                                      :?YJJJJJY55YYYYYYYYYYYYYYJ5&@@@5??!                               :G@
@G:                                              ^777777777777777777!!!~                                   :G@
@G:                                                                                                        :G@
@@&########################################################################################################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::BedroomTableImage()
{
	const char* image = R"(@@&########################################################################################################&@@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                :PP:                                                                    :G@
@G:                              :P@@@&5:                                        .                         :G@
@G:               ^B@@P:?@@@@@J. ~##~  !&G^.:::::::::::::::::::::::::::::::::..?#&#####@#~                 :G@
@G:            :^:7&@#BBBBBBBBBBB#@B^  !&@#BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB##J      .G@J:                :G@
@G:           .G@@@B?.           .B#~  !&P                                             ?B@@J^              :G@
@G:          ~J#@@G.             :B#^  ~&G.                                .7???JJJJJJ7  !G@@Y~            :G@
@G:          P@@@@&5YY55555Y~    :B@GY5B@G.                              :?G@@@B??J?J&@B?  ~5@@P!          :G@
@G:        7G@@Y~^?&@GPPPP&@J    .~!7777!^          .JGGPPGG?            ~&&7J@@P~   :7#@#J  ^Y@@G7        :G@
@G:      7B@@J: .Y#@#J????G@J                    J#B#@@BGG#@@#?          ~#G. :Y@@B7    !B@&5. :J@@B7      :G@
@G:      Y@@&!  ^B@@#Y?J??G@J                  J&@@BPPP555G&@@Y          ^B@@5. .Y@@#####&@@B^   .J@@&?    :G@
@G:   .J@@@@#~.P@@@@#5JYYYB@J                ?@@&G55555PG#5^?#Y            ~B@@Y ?@J      ^##^      ?&@&?. :G@
@G:  7@@@@B!  .Y#BBBBBBBBB#B7              .^5@&GP55PGBB5~7BY                ~G5~5@P^^~~~^7&#^        Y@@&^.G@
@G. !5@&P!                                 J@&55PGBBBGY!?GJ                    ~GGPPGGGGGGGGY:        7G@&J7B@
@#J?JB@J                                   ~YY???JJYJ?J5J                                               Y@@@@@
@@@&YP@#YYYYYYY55555PP7                      :???JJJJJ!                                         ^J5YYYYY#@@@@@
@B7J@@@&####&@@Y!!777!JPGGGGGGGGGGGGGGGGGGGGGPPPP&@@@BPGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGPPB@@###@@Y!B@@@
@G: :J@&GGGGG@&~      .^~~~~~~~~~~~~~~~~~~~~~~~~~^^^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^J@@BGGGG&&7  !B@
@G:  7&@GGGGB@&!                                                                              ~&@GGGGG@&7  :G@
@G:  7&@GGGGB@&!                                                                              !&@BGGGG@&7  :G@
@G:  7&@GGGGB@&!                                                                              !&@BGGGG@&7  :G@
@G:  7&@GGGGB@&!                                                                              !&@BGGGG@&7  :G@
@G:  7&@GGGGB@&!                                                                              !&@BGGGG@&7  :G@
@G:  7&@GGGGB@&!                                                                              !&@BGGGG@&7  :G@
@G:  7&@GGGGB@&!                                                                              !&@BGGGG@&7  :G@
@G:  7&&GGGGG@&!                                                                              !&@GGGGG&&7  :G@
@@&##&@@@@@@@@@&##############################################################################&@@@@@@@@@&##&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::LivingRoomCabinetImage()
{
	const char* image = R"(@@&#################&@@&###############################################################################&@@&&@@
@G:                 !&G.                                                                                P&~.G@
@G:                 ~@B.                                                                               .P&~.G@
@G:               .7Y57.                                                                               .P&~.G@
@G:             .JPY!                                                                                  .P&~.G@
@G:           .JPJ~                                                                                    .P&~.G@
@G:           :B&~                                                                                     .P&~.G@
@G:           :G#~                                                                                     .P&~.G@
@G:         :PB!                                                                                       .P&~.G@
@G:        P@?                                                                                          P@!.G@
@G:      :75P~                                                                                        :!55^:G@
@G:    :?YY^                                                                                          P@?  :G@
@G.  :J#@#YY55555555555555555555YYYYYYYYYYYYYYY555555555555555555555555555555555Y~                    5@?  :G@
@&GPP#@G!~!!777!!!!!!!!!!!!!!!~7B@@@@@@@@@@@@@@P!~!!!!!!!!!!!!!!!!!!!!7777777!!P@@GGGGGGGGGBY.      !P@@?  :G@
@@@@@@@J 7G!   JBBBBBBBBBBBBBBBG5JJJJJJJJJJJJJJPBBBBBBBBBBBBBBBBBBBB#P^         ^^^^^^^^^^^^7P#BBBBB@@5^   :G@
@B~ .J@Y J@@##&@&5????????????J?777777777777777?JJ???????????????????JG&&####################@@@@@5:Y@J    :G@
@G:  7&@@@&57!?#&Y!7777777777777777777777777777777777777777777777777777?????????????????????77775@Y J@J    :G@
@G:  7@@#57!7?Y&&Y!7777777777777777777777777777777777777777777777777777777777777777777777777777?G@Y J@J    :G@
@G. ~YB57!7!?B@&GJ777777777777777777777777777777777777777777777777777777777777777777777777777!Y@@G! J@J    :G@
@#YYB57!777!?B@Y!7777777777777777777777777777777777777777777777777777777777777777777777777777!5@P   Y@J    :G@
@&GY7!77777!?B@Y777777777777777777777777777777777777777777777777777777777777777777777777777!?GGJ~   Y@J    :G@
@#?!7777777!?B@Y!7777777777777777777777777777777777777777777777777777777777777777777777777?GG?^     Y@J    :G@
@#J!7777777!?B@@BJ77777777777777777777777777777777777777777777777777777777777777777777777!J@#:      Y@J    :G@
@#J!7777777777J#&Y!7?77777777777777777777Y#&&&&&&&&@#Y777777777777777777777777777777777!?#B!        Y@J    :G@
@#J!7777777777J#&YJB&&&&&&&&######&@@@@@@G!~!!!~^^^:!G&&#&&&&&&&&&&&@&5???????????77777!?&#~        Y@J    :G@
@#J!7777777?YG###&G!:^^^^^::~!!!!?B@@@@@@@@@@@@5!!777!!7!^:^^^^^^^:^5############PYJYYJJYBP^        Y@J    :G@
@#J!77777J5GG7::^:^^^^^^^:~?G@@@@@@@@@@@@@@@@@@@@@@@@@@@#Y!^:^^^^^^^^^^^^^^^^^^::?BBBGG@@~          J@J    :G@
@#J!!!!JPGP7:^^^^^^^^^^:~JB@@@@@@@@@@@@&P55555P#@@@@@@@@@@&57^^^^^^^^^^^^^^^^^^^^^::^7J5J^        ^?B@?    :G@
@#??PBBG57::^^^^^^^^^^!5#@@@@@@@@@@&5?J7^::::::!JJYB@@@@@@@@G~:^^^^^^^^^^^^^^^^^^^^:^B@7          ?@@@BJ^  :G@
@B7Y@&J!^^^^^^^^^^^^^:J@@@@@@@@@@@@&GPGY^:^^^:^?GPG&@@@@@@@@P~:^^^^^^^^^^^^^^^^^^^^JGY~.          ?@P!G@?  :G@
@@&P7~::^^^^^^^^^^^^::?&@@@@@@@@@@@@@@@@#B###B#&@@@@@@@@@@@@P^:^^^^^^^^^^^^^^^^^^:^P@?          ~G@@? Y@?  :G@
@@@@&#&&&&&&&&&&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&&&&&&&&&&&&&&&&&&@@&##########&@@@&#&@&##&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::LivingRoomCabinetImage(bool)
{
	const char* image = R"(@@&#################&@@&###############################################################################&@@&&@@
@G:                 !&G.                                                                                P&~.G@
@G:                 ~@B.                                                                               .P&~.G@
@G:               .7Y57.                                                                               .P&~.G@
@G:             .JPY!                                                                                  .P&~.G@
@G:           .JPJ~                                                                                    .P&~.G@
@G:           :B&~                                                                                     .P&~.G@
@G:           :G#~                                                                                     .P&~.G@
@G:         :PB!                                                                                       .P&~.G@
@G:        P@?                                                                                          P@!.G@
@G:      :75P~                                                                                        :!55^:G@
@G:    :?YY^                                                                                          P@?  :G@
@G.  :J#@#YY55555555555555555555YYYYYYYYYYYYYYY555555555555555555555555555555555Y~                    5@?  :G@
@&GPP#@G!~!!777!!!!!!!!!!!!!!!~7B@@@@@@@@@@@@@@P!~!!!!!!!!!!!!!!!!!!!!7777777!!P@@GGGGGGGGGBY.      !P@@?  :G@
@@@@@@@J 7G!   JBBBBBBBBBBBBBBBG5JJJJJJJJJJJJJJPBBBBBBBBBBBBBBBBBBBB#P^         ^^^^^^^^^^^^7P#BBBBB@@5^   :G@
@B~ .J@Y J@@##&@&5????????????J?777777777777777?JJ???????????????????JG&&####################@@@@@5:Y@J    :G@
@G:  7&@@@&57!?#&Y!7777777777777777777777777777777777777777777777777777?????????????????????77775@Y J@J    :G@
@G:  7@@#57!7?Y&&Y!7777777777777777777777777777777777777777777777777777777777777777777777777777?G@Y J@J    :G@
@G. ~YB57!7!?B@&GJ777777777777777777777777777777777777777777777777777777777777777777777777777!Y@@G! J@J    :G@
@#YYB57!777!?B@Y!7777777777777777777777777777777777777777777777777777777777777777777777777777!5@P   Y@J    :G@
@&GY7!77777!?B@Y777777777777777777777777777777777777777777777777777777777777777777777777777!?GGJ~   Y@J    :G@
@#?!7777777!?B@Y!7777777777777777777777777777777777777777777777777777777777777777777777777?GG?^     Y@J    :G@
@#J!7777777!?B@@BJ77777777777777777777777777777777777777777777777777777777777777777777777!J@#:      Y@J    :G@
@#J!7777777777J#&Y!7?77777777777777777777Y#&&&&&&&&@#Y777777777777777777777777777777777!?#B!        Y@J    :G@
@#J!7777777777J#&YJB&&&&&&&&&&&&&&&&&&&&&P~^^^^^^^^^!G&&&&&&&&&&&&&&@&5???????????77777!?&#~        Y@J    :G@
@#J!7777777?YG###&G!:^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^:^5############PYJYYJJYBP^        Y@J    :G@
@#J!77777J5GG7::^:^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^::?BBBGG@@~          J@J    :G@
@#J!!!!JPGP7:^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^::^7J5J^        ^?B@?    :G@
@#??PBBG57::^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^:^B@7          ?@@@BJ^  :G@
@B7Y@&J!^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^JGY~.          ?@P!G@?  :G@
@@&P7~::^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^:^P@?          ~G@@? Y@?  :G@
@@@@&#&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@@&##########&@@@&#&@&##&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::BedRoomDrawerImage()
{
	const char* image = R"(@@&#################&@@&###############################################################################&@@&&@@
@G:                 !&G.                                                                                P&~.G@
@G:                 ~@B.                                                                               .P&~.G@
@G:               .7Y57.                                                                               .P&~.G@
@G:             .JPY!                                                                                  .P&~.G@
@G:           .JPJ~                                                                                    .P&~.G@
@G:           :B&~                                                                                     .P&~.G@
@G:           :G#~                                                                                     .P&~.G@
@G:         :PB!                                                                                       .P&~.G@
@G:        P@?                                                                                          P@!.G@
@G:      :75P~                                                                                        :!55^:G@
@G:    :?YY^                                                                                          P@?  :G@
@G.  :J#@#YY55555555555555555555YYYYYYYYYYYYYYY555555555555555555555555555555555Y~                    5@?  :G@
@&GPP#@G!~!!777!!!!!!!!!!!!!!!~7B@@@@@@@@@@@@@@P!~!!!!!!!!!!!!!!!!!!!!7777777!!P@@GGGGGGGGGBY.      !P@@?  :G@
@@@@@@@J 7G!   JBBBBBBBBBBBBBBBG5JJJJJJJJJJJJJJPBBBBBBBBBBBBBBBBBBBB#P^         ^^^^^^^^^^^^7P#BBBBB@@5^   :G@
@B~ .J@Y J@@##&@&5????????????J?777777777777777?JJ???????????????????JG&&####################@@@@@5:Y@J    :G@
@G:  7&@@@&57!?#&Y!7777777777777777777777777777777777777777777777777777?????????????????????77775@Y J@J    :G@
@G:  7@@#57!7?Y&&Y!7777777777777777777777777777777777777777777777777777777777777777777777777777?G@Y J@J    :G@
@G. ~YB57!7!?B@&GJ77777777?555?!7777777777777777777777777777777777777777!?YY7!777777777777777!Y@@G! J@J    :G@
@#YYB57!777!?B@Y!77777!!JPGGBGP5?7777777777777777!7Y5?!!7777777777777?YPPPGPP55PPJ77777777777!5@P   Y@J    :G@
@&GY7!77777!?B@Y!!!!?PGGPPJ7~7B@577777777777777!7YB@@BPG57!!77!!5GY!~?B@@@BB@@@@@&GJ!777777!?GGJ~   Y@J    :G@
@#?!7777777!?B@Y?PBB#@@@@BY7!7B@5777777777777!75BPYJ5&@@@BBB#BBBPYPBB#@@@#?^^J@#YJYGBY7777?GG?^     Y@J    :G@
@#J!77777P#Y7B&~:B@@@@BJP@@###@&Y!7777!JB&#&#57G@57P&@@@@@#Y?JG@&#@@PJ?Y#@BGG#@&#B#@@P777!J@#:      Y@J    :G@
@#J!77777P@@#!:PB! .7#@&&@@@@@@@&&&&&&&&@@@@@@&@&? .:.!B@@@&&#&@@@@@&&#&&@@@@@@@@@@G?777?#B!        Y@J    :G@
@#J!77777!7B@! 5B~^B@@@@@&?  :5@@#7.:. !#@#####&@@@####@@@@@5. :Y@@@@&!        7#@&##@&J?&#~        Y@J    :G@
@#J!777?JJJ#@J:.!B@@&BBB?  ^5@@@@@@@@B~7&G^:^:^P@@&Y!~?P#@@@G75@@@@@@&!              5@PJGP^        Y@J    :G@
@#J!77!YB@@@@@@@@@@@#7^~~!P@@@@@@@@@@@@@@@@@@#GPP&@@@@&JJ&@@@@@@BPPPG5^            :!YG@@~          J@J    :G@
@#J!!?5555P5YJY#@@#Y5@@@@@@@@@@@@@GYYP&@@BYG@J   ~Y#@@@@@@&PG@@@J                  5@BJYJ^        ^?B@?    :G@
@#??P#@@@J   ~Y#@@#Y5&@@@@G?77??77J55G@@@5 7@#YYYJYB@@@@&5!.?@B?^                ~YJJ&@7          ?@@@BJ^  :G@
@B7Y@#J!!JPPP&@@@@@@@@@@@@J !5^ 7G@&J~~~~: .7G@@@@@@@@#Y!:!P&@Y                  J@&PJ~.          ?@P!G@?  :G@
@@&P7~^..Y@@@@&J~~J#@@G7!!^:P@7 5@@B:.5BGBBBB&@5!P@@@@B!.:J@G^                   ?@@@7          ~G@@? Y@?  :G@
@@@@&#&&&@@@@@@&##&@@@@&##&&@@&&&@@@&&@@@@@@@@@&#&@@@@@&&&&@&###&################&@@@&##########&@@@&#&@&##&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::BedRoomDrawerImage(bool)
{
	const char* image = R"(@@&#################&@@&###############################################################################&@@&&@@
@G:                 !&G.                                                                                P&~.G@
@G:                 ~@B.                                                                               .P&~.G@
@G:               .7Y57.                                                                               .P&~.G@
@G:             .JPY!                                                                                  .P&~.G@
@G:           .JPJ~                                                                                    .P&~.G@
@G:           :B&~                                                                                     .P&~.G@
@G:           :G#~                                                                                     .P&~.G@
@G:         :PB!                                                                                       .P&~.G@
@G:        P@?                                                                                          P@!.G@
@G:      :75P~                                                                                        :!55^:G@
@G:    :?YY^                                                                                          P@?  :G@
@G.  :J#@#YY55555555555555555555YYYYYYYYYYYYYYY555555555555555555555555555555555Y~                    5@?  :G@
@&GPP#@G!~!!777!!!!!!!!!!!!!!!~7B@@@@@@@@@@@@@@P!~!!!!!!!!!!!!!!!!!!!!7777777!!P@@GGGGGGGGGBY.      !P@@?  :G@
@@@@@@@J 7G!   JBBBBBBBBBBBBBBBG5JJJJJJJJJJJJJJPBBBBBBBBBBBBBBBBBBBB#P^         ^^^^^^^^^^^^7P#BBBBB@@5^   :G@
@B~ .J@Y J@@##&@&5????????????J?777777777777777?JJ???????????????????JG&&####################@@@@@5:Y@J    :G@
@G:  7&@@@&57!?#&Y!7777777777777777777777777777777777777777777777777777?????????????????????77775@Y J@J    :G@
@G:  7@@#57!7?Y&&Y!7777777777777777777777777777777777777777777777777777777777777777777777777777?G@Y J@J    :G@
@G. ~YB57!7!?B@&GJ77777777777777777777777777777777777!7Y5555555YJ7777777777777777777777777777!Y@@G! J@J    :G@
@#YYB57!777!?B@Y!!!!?5PPGPPPPPPPPPPPPPPPPGGY7!7777?YPPP55555YY#@G!!77777777777777777777777777!5@P   Y@J    :G@
@&GY7!77777!?B@Y75GP#@&J?JJJJJJJJJJJJJJJJ?7YGY777!?#@P!       :?5GY777777777777777777777777!?GGJ~   Y@J    :G@
@#?!7777777!?B&J?#@@#?:                  :Y#@G777!?##~          Y@P77777777777777777777777?GG?^     Y@J    :G@
@#J!7777777!?B@@G7:^:                  ~P&@@@P7!7!?##~          Y@P7777777777777777777777!J@#:      Y@J    :G@
@#J!77777777?B@@B^                     !&P:?@@&&&&&@#~          Y@P77777777777777777777!?#B!        Y@J    :G@
@#J!777777?B@@B~                     ~&B:  ?@P^^^:~B&~          J@@&@&5????????????7777!?&#~        Y@J    :G@
@#J!7777JB@@G~                      :7G5.  ?@P^:^~7GG^          Y@J^P@@@#BBBBBBBB&@GJJYJYBP^        Y@J    :G@
@#J!7!!P@&P~                      :J@#:    ?@P^.~B@!            Y@Y^P@#Y:        ?@@@BG@@~          J@J    :G@
@#J!!?5&@J                      ^Y@@G7.    ?@P^.~G&!          :?B@Y^G&~          ~Y#@PJYJ^        ^?B@?    :G@
@B?7P#@B?^                    ~5@@P!     ^J5Y7:.^P@GYYYYYYYYYYB@#J~~G&!            ?@@@!          ?@@@BJ^  :G@
@&B#@@@Y                    !G@@5^     :5&@P:7GBB&@@@@@@@@@@@@G?^:.~B&!          !P&@5~.          ?@P!G@?  :G@
@@@G~:^.                    5@Y:     ^P&@B7JB@@Y^:^^^^^^^^::J@@B#B7^G&!          J@@@7          ~G@@? Y@?  :G@
@@@&#####&##################&@&##&###&@@@&#&@@@&############&@@@@@&&@@&##########&@@@&##########&@@@&#&@&##&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::BedImage()
{
	const char* image = R"(@@&########################################################################################################&@@
@G:                                                                                                        :G@
@G:                           ^777777777777777777777777777~                                                :G@
@G:                     ^?JJJJ5GGGGGGGGGGGGGGGGGGGGGGGGGGGPJ?JJJJJJJJJJ7.                                  :G@
@G:                     ?@&5557^^^^^^^^^^^^^^^^^^^^^^^^^^^!5P55555555P@@GY55555!                           :G@
@G:                     ?@P^:^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^^^^^^^~7JJJJJJG@@G!                         :G@
@G:                     ?@P~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^^^^~77?PB7                       :G@
@G:                     ?@P~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^5@@#7                     :G@
@G:                     ?@P~^~~~~~~~~~~~~~^^^^^^^^^^^^^^^^~~~~~~~~~~~~~~~~~~~~~~~^~G@J.                    :G@
@G:                     ?@P~^~~~~~^^^^^^^~7777777777777777!~^^^^^^^^^^~~~~~~~~~~~^~Y#@&7                   :G@
@G:                     ?@P~^~~~^~?JJJJ??P&@@@@@@@@@@@@@@@BJ?JJJJJJJJ?!~~~~~~~~~~~~^~G&!                   :G@
@G:                     7@P^:^^^:~JG@@@@@#BBBBBBBBBBBBBBBB#&@@@@@@&@@@J^^~~~~~~~~~~^~G@P7:                 :G@
@G:                   :JB@&GPGGGGP5P&@BGBBBBBBBBBBBBBBBBBBBBBBBBBBBB@&?:^^~~~~~~~~~^~75@@!                 :G@
@G:                 :Y&@B!~7777!~7#@&BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB&@BGBP!:^^^^^^~~~^~B&!                 :G@
@G:               :5@@B~.       J#@@#BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB&@@#7!G&#####Y^^~^!B&!                 :G@
@G:             :P@@G^         .P@&BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB#@#^ .::..?@@&Y~:!B&!                 :G@
@G:        .:.^B&7.:::::::::.:5@@@@@@@@@@@@@@@@@@@@@@#BBBBBBBBBBBB####&G^        ?&@#J!B&!                 :G@
@G:      .~5&&&##&&&&&&&&&&&&&#####################@@@@@@@@@@@@@@@Y^^^^^^:          ^P@@#~                 :G@
@G:  .!!!5#577777777777777777777777777777777777777?P#BBBBBBBBBBBBB#####&@&J^       Y@@@@#~                 :G@
@G. 75B#B577???????????????????????????????????????77777777777777777777?PBBGJ~   :?G@@@@#~                 :G@
@#55G5?77???????????????????????????????????????????????????????????????7775@&5Y5B@@@&#@#~                 :G@
@&GY?7????????????????????????????????????????????????????????????????????7Y&@@G!5@&BGG@#~                 :G@
@#J7????????????????????????????????????????????????????????????????????7JB@@G^7GBBGG#@@&~                 :G@
@#J7?????????????????????????????????????????????????????????????????????Y&G^!B@@#GPG@&?                   :G@
@#J7?????????????????????????????????????????????????????????????????YB&&P.^#@@&GGGGG@&7                   :G@
@#J7????????????????????????????????????????????????????????????JYY5BG^ .^^7G&@&GPGGB#G~                   :G@
@#J7???????????????????????????????????????????????????????777JPPGBP^ :J@@#? ~@@###@@7                     :G@
@#J7??????????????????????????????????????????????????????JPGGG5~   ~Y555?.  ^J5YYY5Y~                     :G@
@#J7???????????????????????????????????????????????????7775@&J^   755?:                                    :G@
@#J7?????????????????????????????????????????????????7JG#&P!. ~GBGY!.                                      :G@
@#J7???????????????????????????????????????????????7JG@@B~!P#BY^^^.                                        :G@
@@&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@@@&#&@@@&############################################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::TelevisionImage()
{
	const char* image = R"(@@&##&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&##&@@
@G. :J&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&!  :G@
@B7J@@@@@@@#BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@Y~ :G@
@@@@@@@@@@@5!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!?PGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGPPB@@@@@@@@@~.G@
@@@@@@@@@@@5!!777777777777777777777777777777777777777777777!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Y&@@@@@@@&~.G@
@@@@@@@@@@@5!!77777777777777777777777777777777777777777777777777777777777777777777777777777777!!5@@@@@@@@#^.G@
@@@@@@@@@GJ77777777777777777777777777777777777777777777777777777777777777777777777777777777777777?P@@@@@@@#B&@
@@@@@@@@@P!!777777777777777777777777777777777777777777777777777777777777777777777777777777777777!!5@@@@@@@@@@@
@@@@@@@@@P7!777777777777777777777777777777777777777777777777777777777777777777777777777777777777!!5@@@@@@@@@@@
@@@@@@@@@P7!777777777777777777777777777777777777777777777777777777777777777777777777777777777777!!5@@@@@@@@@@@
@@@@@@@@@P7!77777777777777777777777777777777777777777777777777777777777777777777777777777777777777YB&@@@@@@@@@
@@@@@@@@@P7!77777777777777777777777777777777777777777777777777777777777777777777777777777777777777!!5@@@@@@@@@
@@@@@@@#5J7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777!7P@@@@@@@@@
@@@@@@@P!!7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777!7P@@@@@@@@@
@@@@@@@P7!7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777!7P@@@@@@@@@
@@@@@@@P7!7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777!7P@@@@@@@@@
@@@@@@@P7!7777777777777777777777777777777777777777777777777777777777777777777777777777777777777777!!P@@@@@@@@@
@@@@@@@P7!77777777777777777777777777777777777777777777777777777777777777777777777777777777777777777JG@@@@@@@@@
@@@@@@@P7!77777777777777777777777777777777777777777777777777777777777777777777777777777777777777!!5@@@@@@@@@@@
@@@@@@@P7!77777777777777777777777777777777777777777777777777777777777777777777777777777777777777!!5@@@@@@@@@@@
@@@@@@@P!!77777777777777777777777777777777777777777777777777777777777777777777777777777777777777!!5@@@@@@@@@@@
@@@@@@@&BY7!777777777777777777777777777777777777777777777777777777777777777777777777777777777777!!5@@@@@@@@@@@
@@@@@@@@@P7!777777777777777777777777777777777777777777777777777777777777777777777777777777777777!!5@@@@@@@@@@@
@@@@@@@@@P7!777777777777777777777777777777777777777777777777777777777777777777777777777777777777!!5@@@@@@@@@@@
@@@@@@@@@P?7777777777777777777777777777777777777777777777777777777777777777777777777777777777777!!5@@@@@@@@@@@
@@@@@@@@@@@5!!77777777777777777777777777777777777777777777777777777777777777777777777777777777777?P@@@@@@@@@@@
@@@@@@@@@@@5!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!77777777777777777777777!!!Y@@@@@@@@@GG&@
@@@@@@@@@@@B55555555555555555555555555555555555555555555555555555555P5?!!!!!!!!!!!!!!!!!!!!!7555G@@@@@@@@&^ G@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@BPPGGGGGGGGGGGGGGGGGPPB@@@@@@@@@@@P7.:G@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@7  :G@
@B~7&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@Y:   :G@
@@#&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&####&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::TelevisionImage(bool)
{
	const char* image = R"(@@&##&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&##&@@
@G. :J&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&!  :G@
@B7J@@@@@@@B555555P&@@@@@@@@@@@@@@@@@&P555555PPPPPPPPPPPPPB@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@Y~ :G@
@@@@@@@@@@@5777777JB&###############&G?777777^            .?YJJJJJJJJJJJJJJJJJYYYYYYYYYYYYYYYYYYG@@@@@@@@@~.G@
@@@@@@@@@@@&&&&&&&#GPPPPPPPPPPPPPPPPPG#&&&&@@Y        .JP55YYYYYYYYYYYYYYYYYY!                  !&@@@@@@@&~.G@
@@@@@@@@@@@BPPPPPPGGGGGGGGGGGGGGGGGGGGGPPPP#@J      .YGJ7?????????????????75@@GPP!              7@@@@@@@@#^.G@
@@@@@@@@@#GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG#@J    .5BJ~.....................^Y@@@@B7             :Y@@@@@@@#B&@
@@@@@@@@@#GPGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG#@J  .5#?:...!B@&5^.:.:...^P@@G~..:^:^5@Y              7@@@@@@@@@@@
@@@@@@@@@#GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG#@J  :G@?  ~B@&&@@&Y:...:5&@@&&@G^ ....:J&@&!          ?@@@@@@@@@@@
@@@@@@@@@#GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG#@? Y@@&7  !#G ~&G: ::::. ^B#::#B^ .:::. :P@7          ?@@@@@@@@@@@
@@@@@@@@@#GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG#@J !G@&7  !&&?Y@G: ::::. ^B@JJ@#^ .:::: .G@7          ~P#@@@@@@@@@
@@@@@@@@@#GPGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG#@Y   P@?. ^JPPP57. ..... .?PPPP?^..::.:!J5J^            ?@@@@@@@@@
@@@@@@@&#GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG#@J  .G@7 .....  ~5P555555Y^  ....:::: .P@?              J@@@@@@@@@
@@@@@@@#GPGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG#@J   ^7PP~ .::..^7G@@@@@@@#5~..::..  ?GY!:              J@@@@@@@@@
@@@@@@@#GPGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG#@J    .G@@P^ .::..:~P@@@@&J~:... !B&#Y^.                J@@@@@@@@@
@@@@@@@#GPGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG&@Y      ~B@@P~.::::::^^^^^:..!G@&P7Y@@#7                J@@@@@@@@@
@@@@@@@#BGBBBBBBBBBBBBBBBBBBBBBBBBBBBBBGGB#&&?      :B&?7B&&&&&&&#####&&&B7~!~~~~5&Y.               J@@@@@@@@@
@@@@@@@&BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB##J         .!GB7^~~~~~~~~~~~~~~~~~~~~~~~~~~5#J:.          .^5@@@@@@@@@
@@@@@@@Y                                          .G@?:^~~~~~~~~~~~~~~~~~~~~~~~~~~~:^B@7          ?@@@@@@@@@@@
@@@@@@@Y                        !JJJJJJJJJJJJJJJJ?Y#@G5555555555555555555555555555555&@P??JJJJJ?^ 7@@@@@@@@@@@
@@@@@@@J                    ~Y555P555555PPP55555PPPYYY5555555555555555555555555555555555PPPP55B@&5G@@@@@@@@@@@
@@@@@@@#P!                !G@@BJ!!5GGGGY~^~?GBGJ~^!5GGGGBB5~?GY~^~~~~~~~~~~~^?GY~?GBG?~~~~~~~~!JJYG@@@@@@@@@@@
@@@@@@@@@J              !BP???!~~7B@@@@@&5!Y@@@5~^7B@@&Y??7~Y@@#Y~~!!!!!!~~?B@@G!5@G?!!!!!!!!!!~~~Y@@@@@@@@@@@
@@@@@@@@@J            !B@@P~~~!!~7B@@B?J@B!Y@@@5~^7G@@#?~~~!!!5@@&Y~~!!!~?B@@B7~~P@P~~!!!!!!!!!!~~Y@@@@@@@@@@@
@@@@@@@@@Y.           ?@B!~!!!!!~7B@@B7?#@@@@@@5~^7G@@@&G7~!!!~!P@57G@@#??&#7~~~~Y&@@Y~~!!!!!!!!~~Y@@@@@@@@@@@
@@@@@@@@@@@?       :?&@&5!~!!!!!~7B@@#7^~JB@@@@5~^7B@@&Y7?7!~!~!Y#@@&###@@&P7~!!!!?B@5~~!!!!!!!!!7P@@@@@@@@@@@
@@@@@@@@@@@7      ^#@BY~^~~~~~~~^!5BB5!^~^^?GBGJ~^!5GGGGBB5!^~~~^~YG?^^7PP7~~!!~~YB#GJ~~!!!!~~~^J@@@@@@@@@GG&@
@@@@@@@@@@@P?????7Y&&5Y55555555555YYYY55555YYYYY555YYYYYYYY5555555YY5Y7^^^~~~~~~~~^^^~~~~~~~!Y5YG@@@@@@@@&^ G@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@BPPPPPPPPPPPPPPPPPPPPPG@@@@@@@@@@@P7.:G@
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@7  :G@
@B~7&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@Y:   :G@
@@#&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&####&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::ToiletCabinetImage()
{
	const char* image = R"(@@&##############&######&######################################################################&######&####&@@
@G:                :^^.                                                                          ^^^.      :G@
@G:               ^#@@#?!77777777777777777777777777777777777!!!7777777777777777777777777777777!!5@@@Y      :G@
@G:               ^#&5Y5555555555555555555555555555555555555B@#555555555555555555555555555555555YYB@Y      :G@
@G:               ~#B.                                      !@5                                   ?@Y      :G@
@G:               ~#B:                                    ^5&@5                                   J@Y      :G@
@G:               ~#B:                                    7@B~.                                   J@Y      :G@
@G:               ~#B:                                    7&P                                     ?@Y      :G@
@G:             ^B#^                                      7&P.                                      Y@J    :G@
@G:             ^##^                                      7&P.                                      Y@J    :G@
@G:             ^##^                                      7&P.                                      Y@J    :G@
@G:             ^##^                                      7&P.                                      Y@J    :G@
@G:             :#&^                                  :J? !&P ^Y!                                   Y@J    :G@
@G:           .JP?^.                                  ~&B:~&5 ?@Y                                   :!YP~  :G@
@G:           :B&~                                    ^#B.~&5 ?@Y                                     5@?  :G@
@G:           :B&~                                    ^B@&&@@&@@J                                     5@?  :G@
@G:           :B&~                                      ~#@@@@Y                                       5@?  :G@
@G:           :B&~                                      ~#@@@@Y                                       5@?  :G@
@G:           :B&~                                      ^#@@@@J                                       5@?  :G@
@G:           :B&~                                    .!5@@@@@B?^                                     5@?  :G@
@G:           :B&~                                    ^&@JY@B?G@Y                                     5@?  :G@
@G:           :B&~                                    ^#G.~&5 7@Y                                     5@?  :G@
@G:           :B&~                                    ^#B.~&5 ?@Y                                     5@?  :G@
@G:           :B&~                                     .. !&P. ..                                     5@?  :G@
@G:           :B&~                                        7&P.                                        5@?  :G@
@G:           .5G7:                                       7&P.                                      .^5B!  :G@
@G:             :##:                                      7&P.                                      Y@J    :G@
@G:             ^#@5~                                     !&P                                     :?B@J    :G@
@G:             .!5@@P555555555555555555555555555555555555B@&5555555555555555555555555555555555555#@#?^    :G@
@G:                ~77777777777777777777777777777777777777!!!77777777777777777777777777777777777777!:      :G@
@G:                                                                                                        :G@
@@&########################################################################################################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::ToiletCabinetImage(bool)
{
	const char* image = R"(@@@@@@@@@@@&##########################################&########################################&######&####&@@
@&BBBBBBB#B?^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                            ^^^.      :G@
@G:        ?GGG&@@@@@#BB############################BJ!!!!!!!!!7777777777777777777777777777777!!5@@@Y      :G@
@G:           .P@BB@&P55J!!!!7777777777777777777777!?PBBBBBB&@#555555555555555555555555555555555YYB@Y      :G@
@G:           :G&J75PPB@@BBGY7!7777777777777777777777!!!!!!!5@Y                                   ?@Y      :G@
@G:           :G@Y7777?Y5555G##BBBBBBBBBBBBBBBBBBBBBBBBBBBBB&@5                                   J@Y      :G@
@G:           :G@Y7777777777?YJY#@GY555555555555555555555YG@G~.                                   J@Y      :G@
@G:           :G@Y777777777777!?B@5??JJJJJJJJJJJJJJJJJJJ??P@5                                     ?@Y      :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJJJJ??P@P.                                      Y@J    :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJJJJJYPBJ.                                      Y@J    :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJJJ?5@G.                                        Y@J    :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJJJ?5@G.                                        Y@J    :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJJJ?5@G.  !Y!                                   Y@J    :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJJ??5@G.  J@Y                                   :!YP~  :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJ?YB@@P.  J@Y                                     5@?  :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJ?5@B~  !#@@J                                     5@?  :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJ?5@B:  ?@5                                       5@?  :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJ?5@G:  ?@5                                       5@?  :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJ?5&#?: 7@5                                       5@?  :G@
@G:           :G@Y7777777777777?B@5?JJJJJJJJJJJJJJJJJ?Y#@@P.7@#?^                                     5@?  :G@
@G:           :G@Y7777777777777?B@5???????????????????Y#@@P..7B@Y                                     5@?  :G@
@G:           :G@Y777777777777!?B@&####################@@@P.  ?@Y                                     5@?  :G@
@G:           :G@Y777777777777P&@&PJJYJJYYYYYYYYYYYYYYJJP@G.  J@Y                                     5@?  :G@
@G:           :G@Y777777777?P@@@5?777777777777777777777!Y@G.  ...                                     5@?  :G@
@G:           :G@Y77777777P@@&57777777777777777777777777Y@G.                                          5@?  :G@
@G:           :G@Y777777?JG#5777777777777777777777777777Y@G.                                        .^5B!  :G@
@#?!77!:      :G@Y77?Y55G#577777777777777777777777777777Y@G.                                        Y@J    :G@
@&PY5#@#J?JY?. G@Y!!Y@@GY!!777777777777777777777777777!!Y@P.                                      :?B@J    :G@
@G.  :?JJJJJJYP&@#GG#@@BGBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB#@&P55555555555555555555555555555555555555#@#?^    :G@
@G:          ^7!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!7777777777777777777777777777777777777777!:      :G@
@G:                                                                                                        :G@
@@&########################################################################################################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::BedroomDoorImage()
{
	const char* image = R"(@@&#####################&##########################################################&#######################&@@
@G:                       .^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^.                         :G@
@G:                       J@&GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG&@Y                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                           .::.   ?@5                         :G@
@G:                       J@J                                         .!P##P~. ?@5                         :G@
@G:                       J@J                                        :#@^  ~@B.7@5                         :G@
@G:                       J@J                                        .?5JJJY5! ?@5                         :G@
@G:                       J@J                                           7YY7   ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@@&#######################&@&##################################################&@&#########################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::ClosetDoorImage()
{
	const char* image = R"(@@&#####################&##########################################################&#######################&@@
@G:                       .^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^.                         :G@
@G:                       J@&GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG&@Y                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                           .::.   ?@5                         :G@
@G:                       J@J                                         .!P##P~. ?@5                         :G@
@G:                       J@J                                        :#@^  ~@B.7@5                         :G@
@G:                       J@J                                        .?5JJJY5! ?@5                         :G@
@G:                       J@J                                           7YY7   ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@@&#######################&@&##################################################&@&#########################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::KitchenDoorImage()
{
	const char* image = R"(@@&#####################&##########################################################&#######################&@@
@G:                       .^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^.                         :G@
@G:                       J@&GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG&@Y                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                           .::.   ?@5                         :G@
@G:                       J@J                                         .!P##P~. ?@5                         :G@
@G:                       J@J                                        :#@^  ~@B.7@5                         :G@
@G:                       J@J                                        .?5JJJY5! ?@5                         :G@
@G:                       J@J                                           7YY7   ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@@&#######################&@&##################################################&@&#########################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::ToiletDoorImage()
{
	const char* image = R"(@@&#####################&##########################################################&#######################&@@
@G:                       .^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^.                         :G@
@G:                       J@&GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG&@Y                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                           .::.   ?@5                         :G@
@G:                       J@J                                         .!P##P~. ?@5                         :G@
@G:                       J@J                                        :#@^  ~@B.7@5                         :G@
@G:                       J@J                                        .?5JJJY5! ?@5                         :G@
@G:                       J@J                                           7YY7   ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@@&#######################&@&##################################################&@&#########################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::ToiletBowlImage()
{
	const char* image = R"(@@&#################&@@###&@@@&##########################################&@@@@&####&@&#####################&@@
@G:                 !@B~  ?@@G!                                          :P@@P     5@?                     :G@
@G:                 ^5&@5 ?@J                                              ^557^   5@?                     :G@
@G:                   !@5 ?@Y                                                7@G.  5@?                     :G@
@G:                   7&#YJ?^                                                7@P.  5@?                     :G@
@G:                   !&@@Y                                                  7@P   5@?                     :G@
@G:                   7&P^JB?                                                .:JB? Y@?                     :G@
@G:                   7@5 ?@Y                                                  ?@Y Y@?                     :G@
@G:                   !#5:J@J                                                 .J@Y Y@?                     :G@
@G:                     7@@@?                                                7&@B7 ?BJ:.                   :G@
@G:                     ?@&PJ!:                                              7@5     P@7                   :G@
@G:                     ?@J Y@?                                              7@G.   .P@7                   :G@
@G:                     ?@Y ^?5Y^                                          :JY?~    .P@7                   :G@
@G:                     ?@5   ^?P5^                                      .Y#@G      .P@7                   :G@
@G:                     ?@5    .P@&BBBBBBBBBB#B7                       :5&@#!.      .P@7                   :G@
@G:                     ?@5      ~B@@#J77????7?P&&##############&#7  :5@@B~    .    .P&7                   :G@
@G:                   !&@&######&@@#J~!!!!!!!!!!7777777777777777!7P&&&@#!^P&#######@&?                     :G@
@G:                   7@P       P@@G?~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~7P&&G!.       5@?                     :G@
@G:                   7@P     :7B&J~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!~~J@&?^     5@?                     :G@
@G:                   ^JY?~  .5@@&J~!!!!!!!!~?5555555555Y!~~~~~~!!!!!!!!!75GBPJ~   5@?                     :G@
@G:                     ?@5  .5@@&J~!!!!!!!?P#@@@@@@@@@@&GPPPPGPJ~~~!!!!!!!~~Y@P   Y@?                     :G@
@G:                     ?@Y  .5@@&J~!!!!!!!5@@###########&&&&&&&#BBGJ!!!!!!!~Y@&P5P&@?                     :G@
@G:                     ?@@B! Y@@&J~!!!!!!!5@@###################&@@Y!!!!!!!!!?P@@@5^.                     :G@
@G:                      .Y@J 5&7:G#J~!!!!!5@@####################@@Y!!!!!!!!!!5@@@?                       :G@
@G:                         5@?  :B&J~!!!!!!!P@@################&@@#Y!!!!!!!~Y&@&@@J                       :G@
@G:                         5@?  :B&?~!!!!!!!Y###@@@&#########@@@#Y!!!!!!!!!7P@5 ?@J                       :G@
@G:                         5@?  :G@P?7!!!!!!!!~!5BBB@@@&&&&@@@BJ~~!!!!!!!~J@@G! J@J                       :G@
@G:                         5@?  :G@@#7~~~~~~!!!!!~~!5GGPPPPGGJ!~!!!!!!~~75P57   J@J                       :G@
@G:                         5@?  .~Y&@BGGGGGPJ~~~~~~~~~~~~~~~~!!!~~~~!YGBGY!     J@J                       :G@
@G:                         5@?     ~!777!!P@@BBBBBBBBBB###B5!~!Y##BB#@@Y^       J@J                       :G@
@G:                         5@?            .^^^^^^^^^^^^^:?&@###J^^^^^^:         J@J                       :G@
@@&#########################&@&###########################&@@@@@&########&#######&@&#######################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::LivingRoomDoorImage()
{
	const char* image = R"(@@&#####################&##########################################################&#######################&@@
@G:                       .^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^.                         :G@
@G:                       J@&GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG&@Y                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                           .::.   ?@5                         :G@
@G:                       J@J                                         .!P##P~. ?@5                         :G@
@G:                       J@J                                        :#@^  ~@B.7@5                         :G@
@G:                       J@J                                        .?5JJJY5! ?@5                         :G@
@G:                       J@J                                           7YY7   ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@@&#######################&@&##################################################&@&#########################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::StoreRoomDoorImage()
{
	const char* image = R"(@@&#####################&##########################################################&#######################&@@
@G:                       .^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^.                         :G@
@G:                       J@&GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG&@Y                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                           .::.   ?@5                         :G@
@G:                       J@J                                         .!P##P~. ?@5                         :G@
@G:                       J@J                                        :#@^  ~@B.7@5                         :G@
@G:                       J@J                                        .?5JJJY5! ?@5                         :G@
@G:                       J@J                                           7YY7   ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@G:                       J@J                                                  ?@5                         :G@
@@&#######################&@&##################################################&@&#########################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::KeyImage()
{
	const char* image = R"(@@&########################################################################################################&@@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                 !55J.                                  :G@
@G:                                                               7G&@@@GPGJ.                              :G@
@G:                                                             7B@@@@@@@@@@BB#J                           :G@
@G:                                                         7#&#@@@@@@@@@@@@@@@@&&&?                       :G@
@G:                                                    ...7#@@@@@@@&7  ^P@&&&##&@@@J                       :G@
@G:                                                  .7#@@@@@@@@@@@&J:         !B&B7                       :G@
@G:                                                 .G@@@@@@#PB@@@@@@@J~!~.                                :G@
@G:                                                ~Y#@@@@&5~ ^YYY#@@@@@@#^                                :G@
@G:                                              !5&@@@@&Y~       ^J&@57?7.                                :G@
@G:                                          !PPP&@@@@&J^           ^!.                                    :G@
@G:                                        !B@@@@@@@&?.                                                    :G@
@G:                                      !#@@@@@&?...                                                      :G@
@G:                            .P@@&&&&&&&&@@Y:.::.                                                        :G@
@G:                           .~P&PJJY5PPP5YJG&&&@&!                                                       :G@
@G:                          .P@GJ5PGB@@GB@&P5YJY#@Y~.                                                     :G@
@G:                          .5@P5&@5J57 .?B@BYJYP#@&~                                                     :G@
@G:                          .5@P5&@P!   :?B@BYYYJY@&~                                                     :G@
@G:                          .5@GJ5G@@GPP#@&P5YYYBBJ~.                                                     :G@
@G:                          .5@@#5J5PPPPP55YYYJY&@!                                                       :G@
@G:                            ^P@@&&&&&@B5JYG@@#?.                                                        :G@
@G:                                    !B@###&#?                                                           :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@@&########################################################################################################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::ClockImage()
{

	const char* image = R"(@@&####################################################################&###################################&@@
@G:                                        .^^^^^^^^^^^^^^^^^^^^^^^^^^                                     :G@
@G:                                 ~7!!!!!5&@&&&&&&&&&&&&&&&&&&&&&&@#J!!!!!!^                             :G@
@G:                           ~JJ??YB@&&&&&BP5PPPGB#######BPPPPPPPPP5P#&&&&@@#J??^                         :G@
@G:                       ~Y55G&&#&#P5PPPG#&&&&&&@@GYYYYYYP#&&&&&&&&##GPPPPGB##@@#Y^                       :G@
@G:                     ~P&@@BGPPPPG#@&@@BJ?JJJJJJ?~^^^^^^~?JJJJJJ?J#@@&@#GPPPPGBB#BP~                     :G@
@G:                   ~G@@&GPPPP#@@#J!777!^^^^^^^^^^~~~~~~^^^^^^^^^^!777!J#@@#PPPPPGB#G~                   :G@
@G:                   7&@GPPB@@&@&J~^^^^^^^~~~~~~~~~~~~~~~~~~~~~~~~^^^^^^^~J&@&@@#PPPGG&B~                 :G@
@G:                 !#&GPPPG&@Y^^~^^^~~~~~~~~~~~~~~~~~~~~~^^^^~~~~~~~~~~~^^^~^^J&@@#GPPPG@B^               :G@
@G:               ^#@GPPPG#@@B?^^^~~~~~~~~~~~~~~~~~~~~~~^^~7!~^~~~~~~~~~~~~~^~~^^J#@@#GPG&B7.              :G@
@G:             .^?B#GPPB@&G?^^~~~~~~~~~~~~~~~~~~~~~~~~~^^J@B~^~~~~~~~~~~~~~~~~~~^^?B@@BP5G@B^             :G@
@G:             :#@GPPPP#@P^:~~~~~~~~~~~~~~~~~~~~~~~^^^^^^J@G~^~~~~~~~~~~~~~~~~~~~~^^?PBBGG@B:             :G@
@G:           .75BBGPPG#GY7~^~~~~~~~~~~~~~~~~~~~~~^^!Y5!::J@B~^~~~~~~~~~~~~~~~~~~~~~^:~G@BPBB57.           :G@
@G:           :G@BPPPP#@P^:~~~~~~~~~~~~~~~~~~~~~~~^^!#&7!PPJ7~^~~~~~~~~~~~~~~~~~~~~~^^~G@BPPB@G:           :G@
@G:           :G@BPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~^^!##!7&B~:^~~~~~~~~~~~~~~~~~~~~~~^^~G@BPPB@G.           :G@
@G:           :G@BPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~^~~?B@@G!^^~~~~~~~~~~~~~~~~~~~~~~^^~G@BPPPPB&5.         :G@
@G:           ^G@BPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^7#@@G!^^~~~~~~~~~~~~~~~~~~~~~~^^~G@BPPPPB@P.         :G@
@G:         .P@BPPPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^7#@&5~^^~~~~~~~~~~~~~~~~~~~~~~^^~5&@@GPPB@P.         :G@
@G:         .P@BPPPPPPB@P~^~~~~~~~~~~~~~~~~~~~~~~~~~^^!PP~:^~~~~~~~~~~~~~~~~~~~~~~~~~~^:~B@BPPB@P.         :G@
@G:         .P@BPPPPPPB@P^:~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~^:~B@BPPB@P.         :G@
@G:         .P@BPPPPPPB@&P?~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~JPBBGPPB@P.         :G@
@G:         .P@BPPPPPPGG&@P~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^:~B@BPPG#@@P.         :G@
@G:         .P@BPPPPPPPP#@P^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^~5#BGPPPB@B!.          :G@
@G:           ^G@BPPPPPP#@P~^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^~5&@@BPPG&@@P.           :G@
@G:           .P&BPPPPPPPP#@Y^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^~5@@@BPPPPB@B^             :G@
@G:             :B@GPPPPPP#&P7~^^^^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^~!P@@&BPPPPG@@&5:             :G@
@G:             ^B@#GPPPPPPP&@G???~^^^^^^~~~~~~~~~~~~~~~~~~~~~~~~~~^^^^^^~?J?5&@&BPPPPPB#BY:               :G@
@G:             .7G@@#GPPPPPB##&@@PYYY5?^:^^^^^^^^^^^^^^^^^^^^^^^^:^?55YY5#&&#PPPPPGB##GJ:                 :G@
@G:                !5@@&&#BPPPPPGB#####BPPPPPPPPPPPPPPPPPPPPPPPPPPPPB####BP5PPPPPB&@@G7.                   :G@
@G:                 .~!!5@@&&&@&&#GPPPPPBBBBBBBBBBBBBBBBBBBBBBBBBBBBGPPPPG#&&&&@@P!!!.                     :G@
@G:                      ^^^^^:~G@@&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@@B~:^^^.                         :G@
@@&#############################&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#######&#######################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::FridgeImage()
{
	const char* image = R"(
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::KitchenTableImage()
{
	const char* image = R"(
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::BarricadeDoorImage()
{
	const char* image = R"(@@&#####################&##########################################################&#######################&@@
@G:                       .^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^.                         :G@
@G:                       J@&GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGPP#@Y                         :G@
@G:                       J@J                                                .7G@BJJJJ7:                   :G@
@G:                       J@J                                     !PP555555555J?7?J?J&@B?:                 :G@
@G:                       J@J                         :5BGGGGGGGGGJ7777777777^ ~P7   :7#@!                 :G@
@G:                       J@J                7B#BBBBB#G7^~~~~~~~~~.            :~:    .G&!                 :G@
@G:                 .     Y@Y  .5&&########&#J:.::::::.                          ?#@#! 5@@G^               :G@
@G:               ~G&######&##&B!          .                            ...7&@#&#? J&J. ~#&~               :G@
@G:             ^##^  .^:                                           :^^7#@#B#J  ^:   J#@@#5^               :G@
@G:             ^##^  ~GJ                                       :!!?#@#GGY.    !G?     G@J^.               :G@
@G:             ^##^                                    .7J????J#@#55J:               .!P@&^               :G@
@G:             ^##:  ~5?                  ^Y55555555YYJP@@@@@#J??:                75!   ^?Y?.             :G@
@G:             ^B@B?  !^     7GGGGGGGGGGGG&@G7!7!!~?&@@@@B7~!:                    ~7. ?GPG@#^             :G@
@G:              .7&@#GGBBBBBB@@J^^~~~~~~~~~^.   JB#P!:^^^:                          ?#@@?^^:              :G@
@G:         .Y&&###&@@@@5^Y@5:::.            ?#@#?.::                               .P@?                   :G@
@G:        5&?  .::.    7#&&##########&5:7&@#?                                 .:.:Y#?                     :G@
@G:      .^G@?  :PP^                ^^^7G&#?                               .^^^?G#B7                       :G@
@G:      Y@&5~                  ~77?PBBJ                                ~!!?P&@B!                          :G@
@G:      Y@7  .7?:        ^?JJJJY5PJ.                               ~??5@@G7 .J#@#J??:                     :G@
@G:      Y@#J: !7:      ^5&@BJJ?:                               !55P@@P??!     :??J#@#5555?.               :G@
@G:      :!B@&GGY:    ^P57!!:                               ~PBGY7777~.            :!!!!?&@#J:             :G@
@G:        .^~~^!P#BBB&@5                               ^P&#5~^~.                    JG~ .7&#^             :G@
@G:             ^B#!.:::.                         :5@&&&P^.:.                        .:.  ^#B^             :G@
@G:         ^P@@G^   :.                      .:.^P@@&#&@B~.:::::::::::::         ?#?    :B#~               :G@
@G:        ?#@@?.   ~B5.               .^~~^~JB#B#G~  :5#BBBBBBBBBBBBB#G7^~~~~~^^^^~~~~^!#&~               :G@
@G:          7G@@Y~     ^7^       ~777!JPGGBG7                         .YBGGGGG#@&GGGGGGGGY:               :G@
@G:            7555JJJ~ ^57   ~JJJ5555P?                                       ?@Y                         :G@
@G:               .7G@@5^ :Y55YJY?.                                            ?@5                         :G@
@G:                  ^5@@G&@G!.                                                ?@5                         :G@
@G:                    :^^5@J                                                  ?@5                         :G@
@@&##################&####&@&##################################################&@&#########################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::KnifeImage()
{
	const char* image = R"(@@&########################################################################################################&@@
@G:                                                                                                        :G@
@G:                                                                        .~77777!:                       :G@
@G:                                                                     !??P@@PY5#@J                       :G@
@G:                                                                   !P@@5??~   J@J                       :G@
@G:                                                                 ?B@@J^       J@J                       :G@
@G:                                                             ?#&B?^^:         J@J                       :G@
@G:                                                         !#@#J:.:           7#@@?                       :G@
@G:                                                      ::.?&Y.              .J@5                         :G@
@G:                                                    :7G&#J               :J@@B?                         :G@
@G:                                                ~77?GY.                 ~&@G7                           :G@
@G:                                              ~Y55PJ.                  !P@G                             :G@
@G:                                            !55?:                    7G@@Y~                             :G@
@G:                                          7G5!.                   .?B@@J:                               :G@
@G:                                        7B5~.                     :B@?.                                 :G@
@G:                                    ~B@&Y:                    .Y&@B!                                    :G@
@G:                                    7@G^..                  .Y@@#!                                      :G@
@G:                                 .7#@@@@@@5^^~~^          ^5@@B!                                        :G@
@G:                               ^?&@@@@@@@@@@#G@@5!!~    ~P@@P!                                          :G@
@G:                           ~??J#@@@@@@@@@@#Y: !55P@@5??P@@5~                                            :G@
@G:                       ~YYY#@@@@@@@@@@@@B?:       !JJJJJ?~                                              :G@
@G:                     ~P&@@@@@@@@@@@@@@B7:                                                               :G@
@G:                 ^P#B#@@@@@@@@@@@@B!:^:                                                                 :G@
@G:                 ~#@@@@@@@@@@@@@B!                                                                      :G@
@G:                   !B@@@@@@&&@B~                                                                        :G@
@G:                     !B#B#B!                                                                            :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@@&########################################################################################################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::HammerAndNailsImage()
{
	const char* image = R"(@@&########################################################################################################&@@
@G:                                                                                                        :G@
@G:                                                 .~!77!^                                                :G@
@G:                                                 :B@PG@@YJJ~                                            :G@
@G:                                                 :B#. !JJJJY5555J:                                      :G@
@G:                                                 :B@B?     :7!7B@&5^                                    :G@
@G:                                                  .7&@&Y.      .^^!P##5:                                :G@
@G:                                                     !#@@Y.         ~B@@5:                              :G@
@G:                                                       !B@#@@Y.         !BP^                            :G@
@G:                                                           !B@@?          !BP~.                         :G@
@G:                                                             J@?            !G57:                       :G@
@G:                                                           :?B@G7:            ~55?:                     :G@
@G:                                                       :JYYB@@@@@!              Y@#J^                   :G@
@G:                                                   .YGPB@@@@@@@@@#5^      ^PBGGG&@@@7                   :G@
@G:                                              J#BBB#@@@@@@@@@@@@@@&!  ^P&#5~^~~~^^G&7                   :G@
@G:                                        7#&&#&@@@@@@@@@@@@@@@@@@@@@&&&G~.:.       P@7                   :G@
@G:                               .::..7#@@@@@@@@@@@@@@@@@@@@&#&&&&&#&#&@#~       ..:G@7                   :G@
@G:                           :^:!B@@@@@@@@@@@@@@@@@@@@#BBB#J          :5##P!^~^^5@@B#G~                   :G@
@G:                       :!~!G@@@@@@@@@@@@@@@@@@@@BPGY.                   ^5BGGGGP!                       :G@
@G:                     :7G@@@@@@@@@@@@@@@@@@BYYY5J:                                 !J:                   :G@
@G:                     ?@@@@@@@@@@@@@@@@BJ??^            ~5?        .JY:            ~?YY5J:               :G@
@G:                     7@@@@@@@@@@@@#?~!^                .~JPGP!     ^75GGJ.      7PPP@@@&^               :G@
@G:                     ?@@@@@@&?:^^^:                  ^P#B#@@@J   J#BB@@@G:  !B#B@@Y^^^:!GP:             :G@
@G:                      .Y@Y...                    :P&#&@G^.:.:Y&&#&@@#! .!B&#&@@@Y.      ::              :G@
@G:                                             ^P@&#@#!   .?&@#&#7 .:.~B@@@&Y. :.:5@@&!                   :G@
@G:                                            7B@&7~B@@G.:G&B7  ^^!B@&BGGB5~:^Y@@BBB#G?^.                 :G@
@G:                                          :!~7B@#PPPP5?^  ~!7G@&GG5: :~~Y@@GGP!     YP~                 :G@
@G:                                      :7?JB@#55J:    :Y5JG@&55Y^   !5@@G557                             :G@
@G:                                    ^Y#@#J??^          :?Y?^      .7JJ!                                 :G@
@G:                                    :!7!:                                                               :G@
@G:                                                                                                        :G@
@@&########################################################################################################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}


void InteractionsManager::PlanksItemImage()
{
	const char* image = R"(@@&########################################################################################################&@@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                           ~PGGGGG5^                                    :G@
@G:                                                       ~G#B&@BJ?Y#@&B#5:                                :G@
@G:                                                 :P&&&&GJ????77!77????YB&#&&Y.                          :G@
@G:                                        .:.:Y&&&&#J777777777777777777777777?P@@#?                       :G@
@G:                                    .^^^J#@#5!!777777777777777777777!!7?J?P@@B7                         :G@
@G:                               ~77!!JB&#5!!!777777777777777777777!7J5YP@@@&P!                           :G@
@G:                         ^????JPBBBBP7!!!7777777777777777777!!!!7YPGGGGGGG5??JJJJ?:                     :G@
@G:  ^Y5555555555555555555YY#@@@#5?!!!!!77777777777777777!!!!!JGBGGGG5?!!!!!!?PGPPP&@#J:                   :G@
@G:  ?@&5Y5555555555555YYY#@BYYY7!7777777777777777777!!!?G#B##G5Y55Y?!77777777!!!!!?Y#@#PPGGY.             :G@
@G:  ?@G!!!!!!!!!!!!!!JB&#PJ7!!!7777777777777777777!?G&&BYJJJJ?!!!!!777777777777777!7G@PJJJJ5G#B#B?        :G@
@G:  7&@&@&577777!JB@&GJ??777777777777777777777777?B#Y???7!777777777777777777777777!7G@@#J!!7???P@5        :G@
@G: ..:J&@&&&&&@@@BJ777777777777777777777!77?P&&&&#Y!!!!7777777????????????????????P&&&@#J!777!!5&5:       :G@
@G.~&@#5!!!!!?YBBJ!777777777777777777!!7JJJP#5!!!?JJJJJJJJJJJJP#&################&#5!!7!!!!!!!!!!!P@Y      :G@
@G.~@&5Y555YYGGJ!777777777777777!!!7JYY5GBBPYJYJY#@#BBBBBBBBBBY!~!!!!!!!!!!!!!!!!!!!!!7JY555555555#@Y      :G@
@G::J5555Y5&@BY7!7777777777777!7JPPG@@@@P55#@@@@@@@B55PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPG@@GY55555555Y!      :G@
@G:        ^J&@#5?!77777777!!!YB@@P?????JJJ?????????JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ7.                 :G@
@G:          :?&@J~!!777!!YB#BY!!~.                                                                        :G@
@G:            .!G&&G?!!Y#@@5^                                                                             :G@
@G:               !#@&&&@@Y.                                                                               :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@@&########################################################################################################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::SoapImage()
{
	const char* image = R"(@@&##########################################&########&####################################################&@@
@G:                                            .^^^^:                                                      :G@
@G:                                            Y@@@@&J~!7777777777777!.                                    :G@
@G:                                            5@@@@@@@PJYYYYYYYYY5555J????!.                              :G@
@G:                                            ^J#@@@@&5JJJYYYYY5Y^   P@@@@B:                              :G@
@G:                                              ^!~?#&?J@#?!777!7YGGB@&J~!~.                              :G@
@G:                                                 :B#:^&G.      :~~~^:                                   :G@
@G:                                                 :B#:^&G.                                               :G@
@G:                                   .::::::::::::.~##~!&B^ .J@@&&&&&&&@G^                                :G@
@G:                                  ~#@&#####################&#Y!~!!!~?&B^                                :G@
@G:                                  ~##7~!!!!!!!!!!!!!!!!!!!!!!!!!!!!~?&B^                                :G@
@G:                                  ~##7~!!!!!!!!~~!!!!!!~~!!!!!!!!!!~?&B^                                :G@
@G:                                  ~##7~!!!!!!!YGGGGGGGGGGY!~!!!!!!!~?&B^                                :G@
@G:                                  ~##7~!!!!!~7B@GYYYYYYG@@#Y!!!!!!!~?&#^                                :G@
@G:                                  ~#@&P7!!!!~7B@Y~~!!!!7?JJ?!!!!!!7GB7:                                 :G@
@G:                                    7&B7~!!!~7B@Y!!!!!!!!!!!!!!!!~7##~                                  :G@
@G:                                    !&B7~!!!!7P@@&Y!!!!!!!!!!!!!!~7#&~                                  :G@
@G:                                    !&B7~!!!!!~7P&@&Y7!!!!!!!!!!!7JGP^                                  :G@
@G:                                    !@#!~!!!!!!!~75#@@5?!!!!!!!~7#&!                                    :G@
@G:                                    ^J55J!!!!!!!!!~75#@@PJ!!!!!~7B&!                                    :G@
@G:                                      7@B!~!!!!~~!!!~!JG@B7~!!!~7B&!                                    :G@
@G:                                      7@B!!!!75##P77PBB#@B7~!!!~7B&!                                    :G@
@G:                                      7@B!!!!!7Y#@&&@&Y??7!!!!!~7B&!                                    :G@
@G:                                      7&G7!!!!!!777777!!!!!!!!!~7B&!                                    :G@
@G:                                        ?@G!!!!!!!!!!!!!!!!!!!!~7B&!                                    :G@
@G:                                        ?@G!~!!!!!!!!!!!!!!!!!!~!B&!                                    :G@
@G:                                        ?@#J7~~!!!!!!!!!!!!~!?5Y5@@!                                    :G@
@G:                                        ?@@@#PPPPPPPPPPPPPPPP55555J^                                    :G@
@G:                                        ^????JJJJJJJJJJJJJJJJ^                                          :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@@&########################################################################################################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::DuctTapeImage()
{
	const char* image = R"(@@&########################################################################################################&@@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                            ^!!!!!!!!!!^                                                :G@
@G:                            .   .~77777777777????77Y&#J777777777777777~.   .                            :G@
@G:                        ...^7?JJ??5&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&5??JJ?7^.                          :G@
@G:                       ^777?Y#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#5J7~:.                       :G@
@G:                       ^7!7B@@@@@@@@@@@@@@@@@@PJJJJJJJJP&@@@@@@@@@@@@@@@@@@BY!!7^                       :G@
@G:                       ^7!!J55YYP&@@@@@@@@@@@@GJJJJJJJJP&@@@@@@@@@@@@@@@&P?~?P57:                       :G@
@G:                       :75BBGGGGGYJJJJJJJJJJJJY5&@@@@@@@@@@@@@@GJJJJJJJJ?~?G@@G7:                       :G@
@G:                       :7G@@@@@@@#B##########BJ!7??????????????!!5########&@@@P7:                       :G@
@G:                       :7P@@@@@@@@@@@@@@@@@@@@@&&&&&&&&&&&&&&&&&&@@@@@@@@@@@@@P7:                       :G@
@G:                       :7G@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@P7:                       :G@
@G:                       :7P###@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@G7:                       :G@
@G:                       :~~^~7P#BBBBBBB#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@BY~.                       :G@
@G:                           :^^::^^^^::7PGGGGGGGGPG&@@@@@@@@#PPGGGGGGGGGGGGGGJ^.                         :G@
@G:                                       :::::::.:~7YPP5555PPJ!^::::::::::::::.                           :G@
@G:                                                .:..........:.                                          :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@@&########################################################################################################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::MetalPanImage()
{
	const char* image = R"(@@&########################################################################################################&@@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                 .7JJ???????JJ7.                                                                        :G@
@G:              ?555GBBBBBBBBBBBG5Y5557                                                                   :G@
@G:           .?B@@B5J?JJJJJJJJJ?J5GPB@@GPG7                                                               :G@
@G:           .G@GYJJJJJJJJJJJJJJJJJJJY55B@5                                                               :G@
@G:         .5&PJJJJJJYYYYYYYYYYYYJJJJJJJJYP#@#7                                                           :G@
@G:         .P@P?JJJYY5YYYYYYYYYYYYY5YJJJJJJJB&J.                                                          :G@
@G:        .~P#5JJJY5YYYYYYYYYYYYYYYY55YJJJJJ?J#@Y:                                                        :G@
@G:        5@G?JJJJY5YYYYYYYYYYYYYYYYYY55YJJJJJP#@@!                                                       :G@
@G:        5@GJJJJJY5YYYYYYYYYYYYYYYYYY55YYJJJJ?J#&!                                                       :G@
@G:        5@GJJJJJY5YYYYYYYYYYYYYYYYYYYY55YJJJJJ#&~                                                       :G@
@G:        5@G?JJJJJYY5YYYYYYYYYYYYYYYYYY55YJJJJJ#@#Y^                                                     :G@
@G:        .~P#5JJJJJY5YYYYYYYYYYYYYYYYYY55YJJJJJY5@&~                                                     :G@
@G:         .P@PJJJJJY5YYYYYYYYYYYYYYYY55YJJJJJJJ?Y&#~                                                     :G@
@G:         .P@GJJJJJJYYY555YYYYYYYYYY555YJJJJJJJB@@#!...                                                  :G@
@G:         .J#@&5?JJJJJJYYYY55555555YYYYYJJJJJ?JB@@@@@@B!.                                                :G@
@G:           .G@B5JJJJJJJJJYYYYYYYYYYJJJJJJJJJYP#@@@@@@@@B7:                                              :G@
@G:           .7P@@B5J?JJJJJJJJJJJJJJJJJJJJ?JYG&@@@@@@@@@@@@B???^                                          :G@
@G:              ~5@@&PJ?JJJJJJJJJJJJJJ??5B##@@G?7J#@@@@@@@@@@@@BYYJ^                                      :G@
@G:                ~!!J#&##############&&P7!!!!:   :?#@@@@@@@@@@@@@@#5:                                    :G@
@G:                   .^~^^^^^^^^^^^^^^~~:           .7#@@@@@@@@@@@@@@&P^                                  :G@
@G:                                                     !#@@@@@@@@@@@@@@@P^                                :G@
@G:                                                       !B@#&@@@@@@@@@@@@@@P.                            :G@
@G:                                                           !B@@@@@@@@@@@@@P.                            :G@
@G:                                                             !P&@@@@@@@GPG?.                            :G@
@G:                                                               !Y5YYY5?.                                :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@@&########################################################################################################&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);
}

void InteractionsManager::EmptyBoxImage()
{
	const char* image = R"(@@&########################################################################################################&@@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:                                                                                                        :G@
@G:             .YBGJ.                                                                                     :G@
@G:           .5B5P@@#J.                                                                                   :G@
@G:           :G@Y7?5&@&Y                                                                                  :G@
@G:         .P@57?????5&P:                                                                   .::::..Y@@&@&!^G@
@G:        .~P#Y7?????775&5^^^.                                                          :^^7B@&&&&&&#5?P&&&@@
@G:      :!P#577????????775#@@5~.                                                       .B@@GJ77777777???77J#@
@G:      Y@G77????????????77YG@@! !7.                                                ~JJJPPJ7?????????????7J#@
@G:    ~5PPY????????????????77YP5P@@G7                                           ~555PGGPJ7???????????????7J#@
@G:  ~PGPJ77??????????????????7?YPYP@@GPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPGPPPPJ777?????????????????7J#@
@G:^G@@B?7??????????????????????7?G&@&GPPGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGPP#@#Y??7??????????????????????7J#@
@G:!&#J???????????????????????7?G@@&PP&#5Y555555555555555555555555555555555YYG@@&P????????????????????????7J#@
@@&&@G?7???????????????????????J#@GYYP@&5Y5555555555555555555555555555555555YG@#5B@P?7????????????????????7J#@
@#J7????????????????????????7?B@@#PYYP@&5Y5555555555555555555555555555555555YG@#5B@P77????????????????????7J#@
@#J7??????????????????????77J5B#PYY5YP@&5Y5555555555555555555555555555555555YG@#5G#G5J????????????????????7J#@
@#J7??????????????????????JP&@BYY555YP@&5Y5555555555555555555555555555555555YG@#5YY#@P77??????????????????7J#@
@#J7????????????????????77P@&GP55555YP@&5Y5555555555555555555555555555555555YG@#5Y5PGBGY??????????????????7J#@
@#J7????????????????????YB@@BYY55555YP@&5Y5555555555555555555555555555555555YG@#5Y5Y5#@57?????????????????7J#@
@#J7??????????????????77P@&P55555555YP@&5Y555555555555555555555555555555555YYG@#5Y5Y5#@57?????????????????7J#@
@#J7?????????????????75&@@B5Y5555555555G&@&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&@@#P5555Y5#@5??????????????????7J#@
@#J7?????????????????75@#5Y555555555YP&@BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB#@#5Y555Y5#&57???????????????7J#@
@#J7?????????????????JG@#5Y5555555555G&&BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB#@#5Y555Y5&&57???????????????7J#@
@#J7???????????????7Y@@#G5Y5555555YP&@BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB#@#5Y555Y5&@Y7???????????????7J#@
@#J7?????????????7?5GBG5Y555555555GB##BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB#&#BP555Y5GBG5J??????????????7J#@
@#J7???????????7?P#@&5Y555555555YP&@#BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB&@#5Y555Y5&&Y7?????????????7J#@
@#J7?????????7?PBBGGP55555555555Y5&@#BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB#@B5Y555YP&&Y7?????????????7J#@
@#J7???????7?P&@&PYYY555555555Y5B&#BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB#@B5Y555Y5&&Y7?????????????7J#@
@@&&&&&&&&&&&@@@@@&&&&&&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&&@@@&&&&&&&&&&&&&&&&&@@
)";
	Scene::DrawASCII_Art(image, 0, 0, 15);

}

//robber interaction

//void InteractionsManager::robBedroomDoorInteracted(GameObject* BedroomDoor, GameObject* robber)
//{
	//timer.increaseTimeTaken(5);
//}
