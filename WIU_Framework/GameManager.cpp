#include "GameManager.h"
#include "Scene.h"
#include "MyFunctions.cpp"
#include "Application.h"
#include "Windows.h"
#include "SceneManager.h"
#include "MainMenu.h"
#include "Player.h"
#include "conio.h"
#include "LivingRoomScene.h"
#include "ToiletScene.h"
#include "BedroomScene.h"
#include "StoreRoomScene.h"
#include "KitchenScene.h"
#include "Endings.h"
#include "Furniture.h"
#include "Scene.h"
using namespace myFunctions;

GameManager* GameManager::GM_Instance = nullptr;

GameManager::GameManager(void) : TimeSys()
{
	whatScenePlayerIn = "";
	GM_Instance = this;
	GameEnded = false;
	GameWon = true;
	player = nullptr;
	LoopStarted = false;
	DontCountTime = TimeSys.TimeLoop == 0;
	gameUI = new UI(Vector2(130, 12), 0, 150);
	gameUI->CreateOptionUI(Vector2(POINTX, POINTY), false);
	endingMgr = new EndingManager();
}

GameManager::~GameManager(void)
{
	delete gameUI;
	delete endingMgr;
}

GameManager* GameManager::getGM()
{
	return GM_Instance;
}

void GameManager::Start()
{

	GM_Instance = this;
	GameEnded = false;
	GameWon = true;
	InteractionsMgr.Start();
	DontCountTime = TimeSys.TimeLoop == 0;
}
void GameManager::Update()
{
	whatScenePlayerIn = SceneManager::currentScene->getName();

	if (!LoopStarted) {
		ClearDialogue();
		InteractionsMgr.Start(LoopStarted);
	}
	inventory.DisplayItems();

	if (TimeSys.TimeTaken >= TimeSys.RobberTime or InteractionsMgr.isPlayerSucide or InteractionsMgr.isPlayerHidden or InteractionsMgr.isPlayerSleeping)
	{
		if (DontCountTime)
			return;
		TimeSys.TimeTaken = TimeSys.RobberTime;
		endingMgr->Start();
	}
	else 
	{
		objManager.displayObjectives();
		HandleInput();
	}
}

void GameManager::Exit()
{

}

void GameManager::PromptInput()
{
	Scene::GotoXY(110, 36);
	cout << "Input:";
	Scene::GotoXY(117, 36);
}

void GameManager::HandleInput(void)
{
	if (player == nullptr || TimeSys.TimeTaken >= TimeSys.RobberTime)
		return;
	Application::ShowCursor();

	Furniture* furnituresLeft, * furnituresRight, * furnituresUp, * furnituresDown;
	furnituresLeft = dynamic_cast<Furniture*>(SceneManager::currentScene->GetObjectManager()->GetObjectAtPosition(Vector2(player->GetPosition()->GetX() - 1, player->GetPosition()->GetY())));
	furnituresRight = dynamic_cast<Furniture*>(SceneManager::currentScene->GetObjectManager()->GetObjectAtPosition(Vector2(player->GetPosition()->GetX() + 1, player->GetPosition()->GetY())));
	furnituresUp = dynamic_cast<Furniture*>(SceneManager::currentScene->GetObjectManager()->GetObjectAtPosition(Vector2(player->GetPosition()->GetX(), player->GetPosition()->GetY() - 1)));
	furnituresDown = dynamic_cast<Furniture*>(SceneManager::currentScene->GetObjectManager()->GetObjectAtPosition(Vector2(player->GetPosition()->GetX(), player->GetPosition()->GetY() + 1)));
	
	Furniture*** lists = new Furniture**[4];
	lists[0] = &furnituresLeft; 
	lists[1] = &furnituresRight; 
	lists[2] = &furnituresUp; 
	lists[3] = &furnituresDown; 
	int loopCount;
	for (int i = 0; i < 4; i++)
	{
		loopCount = 0;

		for (int x = i+1; loopCount < 3; loopCount++)
		{
			if (x >= 4)
				x = 0;
			if (*lists[i] && *lists[x]) {
				if ((*lists[i])->GetName() == (*lists[x])->GetName()) {
					*lists[x] = nullptr;
				}
			}
			x++;
		}


	}
	delete[] lists;
	Furniture::TypeOfFurniture typeofFurniture;
	std::string ToPrint = "blank";
	if (furnituresLeft || furnituresRight || furnituresUp || furnituresDown)
		ToPrint = "There is a ";
	if (furnituresLeft)
	{
		ToPrint += furnituresLeft->GetName();
	}
	if (furnituresRight)
	{
		if (furnituresLeft)
			ToPrint += " and a ";
		ToPrint += furnituresRight->GetName();
	}
	if (furnituresUp)
	{
		if (furnituresLeft || furnituresRight)
			ToPrint += " and a ";
		ToPrint += furnituresUp->GetName();
	}
	if (furnituresDown)
	{

		if (furnituresLeft || furnituresRight || furnituresUp)
			ToPrint += " and a ";
		typeofFurniture = furnituresDown->GetFurnitureType();
		ToPrint += furnituresDown->GetName();
		
	}
	if (ToPrint != "blank")
		ToPrint += " next to you.";
	else
		ToPrint = "There is nothing around you.";

	ClearDialogue();
	UI ui(Vector2(Application::numberOfColumns / 2 - 171 / 2, 35), 0, 166);
	ui.CreateText("Enter 'w' or 'a' or 's' or 'd' to move yourself. ", Vector2(3, 2));

	ui.CreateText("[ (W)(A)(S)(D): Move  (/): To enable input field ]", Vector2(10, 0));
	Scene::GotoXY(Application::numberOfColumns / 2 - 81, 45);
	cout<< "Input: ";
	char input;
	if (LoopStarted)
		input = _getch();
	else 
	{
		input = '/';
		LoopStarted = true;
	}



	switch (input)
	{
	case 'w':
		//Move up
		*player->GetPosition() += Vector2(0, -1);
		TimeSys.increaseTimeTaken(1);
		break;
	case 's':
		*player->GetPosition() += Vector2(0, 1);
		TimeSys.increaseTimeTaken(1);
		//Move down
		break;
	case 'd':
		*player->GetPosition() += Vector2(1, 0);
		TimeSys.increaseTimeTaken(1);
		//Move right
		break;
	case 'a':
		*player->GetPosition() += Vector2(-1, 0);
		TimeSys.increaseTimeTaken(1);
		//Move left
		break;
	case '/':
		ClearDialogue();
		string stringInput = "";
		string ItemFromInput = "";
		string KeywordFromInput = "";
		while (true) 
		{
			//					[ (W)(A)(S)(D): Move  (/): To enable input field ]
			ui.CreateText("[ Options: 'E', 'Interact', 'Move', 'Use', 'Help'     ]", Vector2(10, 0));

			std::string Print = "blank", doorStr = "blank";
			if (furnituresLeft || furnituresRight || furnituresUp || furnituresDown)
				Print = "What do you want to do with ";
			else
				Print = "What do you want to do?";
			if (furnituresLeft)
			{
				Print += furnituresLeft->GetName();
				if (furnituresLeft->GetFurnitureType() == Furniture::BedRoomDoor || furnituresLeft->GetFurnitureType() == Furniture::KitchenDoor
					|| furnituresLeft->GetFurnitureType() == Furniture::LivingRoomDoor || furnituresLeft->GetFurnitureType() == Furniture::MainDoor
					|| furnituresLeft->GetFurnitureType() == Furniture::StoreRoomDoor || furnituresLeft->GetFurnitureType() == Furniture::ToiletDoor)
					doorStr = furnituresLeft->GetName();
			}
			if (furnituresRight)
			{
				if (furnituresLeft)
					Print += " or ";
				Print += furnituresRight->GetName();
				if (furnituresRight->GetFurnitureType() == Furniture::BedRoomDoor || furnituresRight->GetFurnitureType() == Furniture::KitchenDoor
					|| furnituresRight->GetFurnitureType() == Furniture::LivingRoomDoor || furnituresRight->GetFurnitureType() == Furniture::MainDoor
					|| furnituresRight->GetFurnitureType() == Furniture::StoreRoomDoor || furnituresRight->GetFurnitureType() == Furniture::ToiletDoor)
					doorStr = furnituresRight->GetName();
			}
			if (furnituresUp)
			{
				if (furnituresLeft || furnituresRight)
					Print += " or ";
				Print += furnituresUp->GetName();			
				if (furnituresUp->GetFurnitureType() == Furniture::BedRoomDoor || furnituresUp->GetFurnitureType() == Furniture::KitchenDoor
					|| furnituresUp->GetFurnitureType() == Furniture::LivingRoomDoor || furnituresUp->GetFurnitureType() == Furniture::MainDoor
					|| furnituresUp->GetFurnitureType() == Furniture::StoreRoomDoor || furnituresUp->GetFurnitureType() == Furniture::ToiletDoor)
					doorStr = furnituresUp->GetName();
			}
			if (furnituresDown)
			{

				if (furnituresLeft || furnituresRight || furnituresUp)
					Print += " or ";
				Print += furnituresDown->GetName();
				if (furnituresDown->GetFurnitureType() == Furniture::BedRoomDoor || furnituresDown->GetFurnitureType() == Furniture::KitchenDoor
					|| furnituresDown->GetFurnitureType() == Furniture::LivingRoomDoor || furnituresDown->GetFurnitureType() == Furniture::MainDoor
					|| furnituresDown->GetFurnitureType() == Furniture::StoreRoomDoor || furnituresDown->GetFurnitureType() == Furniture::ToiletDoor)
					doorStr = furnituresDown->GetName();

			}

			if (EmptyDialogue) {

				ui.CreateText(Print, Vector2(3, 2));
				int yOffset = 1;
				int xOffset = 0;
				if (furnituresLeft || furnituresRight || furnituresUp || furnituresDown) {
					string text = "";
#pragma region OMG
					int doorCount = 0, furnitureCount = 0;
					if (furnituresLeft)
					{
						if (furnituresLeft->GetFurnitureType() == Furniture::BedRoomDoor || furnituresLeft->GetFurnitureType() == Furniture::KitchenDoor
							|| furnituresLeft->GetFurnitureType() == Furniture::LivingRoomDoor || furnituresLeft->GetFurnitureType() == Furniture::MainDoor
							|| furnituresLeft->GetFurnitureType() == Furniture::StoreRoomDoor || furnituresLeft->GetFurnitureType() == Furniture::ToiletDoor) {
							doorCount++;
							text = "";
						}
						furnitureCount++;
					}
					if (furnituresRight)
					{
						if (furnituresRight->GetFurnitureType() == Furniture::BedRoomDoor || furnituresRight->GetFurnitureType() == Furniture::KitchenDoor
							|| furnituresRight->GetFurnitureType() == Furniture::LivingRoomDoor || furnituresRight->GetFurnitureType() == Furniture::MainDoor
							|| furnituresRight->GetFurnitureType() == Furniture::StoreRoomDoor || furnituresRight->GetFurnitureType() == Furniture::ToiletDoor) {
							doorCount++;
							text = "";
						}
						furnitureCount++;

					}
					if (furnituresUp)
					{
						if (furnituresUp->GetFurnitureType() == Furniture::BedRoomDoor || furnituresUp->GetFurnitureType() == Furniture::KitchenDoor
							|| furnituresUp->GetFurnitureType() == Furniture::LivingRoomDoor || furnituresUp->GetFurnitureType() == Furniture::MainDoor
							|| furnituresUp->GetFurnitureType() == Furniture::StoreRoomDoor || furnituresUp->GetFurnitureType() == Furniture::ToiletDoor) {
							doorCount++;
							text = "";
						}
						furnitureCount++;

					}
					if (furnituresDown)
					{

						if (furnituresDown->GetFurnitureType() == Furniture::BedRoomDoor || furnituresDown->GetFurnitureType() == Furniture::KitchenDoor
							|| furnituresDown->GetFurnitureType() == Furniture::LivingRoomDoor || furnituresDown->GetFurnitureType() == Furniture::MainDoor
							|| furnituresDown->GetFurnitureType() == Furniture::StoreRoomDoor || furnituresDown->GetFurnitureType() == Furniture::ToiletDoor) {
							doorCount++;
							text = "";
						}
						furnitureCount++;

					}
#pragma endregion
					if ((doorCount > 0 && doorCount < furnitureCount) || doorCount == 0)
					{
						text = "Enter 'interact' or 'i' (space) <Object name>   |";
					}
					if (text != "") {

						ui.CreateText(text, Vector2(3, 3));
						xOffset = 50 + 4;
					}
				}
				else 
				{
					ui.CreateText("Enter 'move' or Press (Enter)  |", Vector2(3, 3));
					xOffset = 33 + 4;
				}
				if (doorStr != "blank") {
					string doortext = "Enter 'e' to open " + doorStr + " and enter.  |";
					if (xOffset == 0)
						xOffset = 3;
					ui.CreateText(doortext, Vector2(xOffset, 3));
					xOffset += doortext.length() + 3;
				}
				
				if (inventory.GetItemsCount() > 0) 
				{
					ui.CreateText("Enter 'use' (space) <item name> 'on' <object name>", Vector2(xOffset, 3));
				}
				if (furnituresUp) 
				{
					//ui.CreateText("|", Vector2(50, 4 + yOffset));
					if (furnituresUp->GetName() != doorStr) {

						ui.CreateText("  - "+furnituresUp->GetName(), Vector2(3, 4 + yOffset));
					}
					yOffset++;
				}
				if (furnituresDown)
				{
					//ui.CreateText("|", Vector2(50, 4 + yOffset));
					if (furnituresDown->GetName() != doorStr) {

						ui.CreateText("  - " + furnituresDown->GetName(), Vector2(3, 4 + yOffset));
					}
					yOffset++;
				}
				if (furnituresRight)
				{
					//ui.CreateText("|", Vector2(50, 4 + yOffset));
					if (furnituresRight->GetName() != doorStr) {

						ui.CreateText("  - " + furnituresRight->GetName(), Vector2(3, 4 + yOffset));
					}
					yOffset++;
				}
				if (furnituresLeft)
				{
					//ui.CreateText("|", Vector2(50, 4 + yOffset));
					if (furnituresLeft->GetName() != doorStr) {

						ui.CreateText("  - " + furnituresLeft->GetName(), Vector2(3, 4 + yOffset));
					}
					yOffset++;
				}
			}
			stringInput = InputField();
			ItemFromInput = "";
			KeywordFromInput = "";
			//move for doors only
			if (stringInput.empty())
				break;

			int chCount = 0;
			for (char ch : stringInput)
			{
				if (ch == ' ')
				{
					chCount++; 
					break;
				}
				else
					chCount++;
			}
			for (int i = 0; i < chCount-1; i++)
			{
				KeywordFromInput += stringInput[i];
			}
			for (int i = chCount; i < stringInput.length(); i++)
			{
				ItemFromInput += stringInput[i];
			}
			if ((KeywordFromInput == "interact" || KeywordFromInput == "i") && ItemFromInput != "")
			{
				bool checkValidInput = false; 
				if (furnituresUp) 
				{

					std::string strName = furnituresUp->GetName();
					strName = Scene::tolowerString(strName);
					if (ItemFromInput == strName) {
						furnituresUp->InteractFurniture(player);
					}
					if (!checkValidInput)
						checkValidInput = (ItemFromInput == strName);
				}
				if (furnituresLeft) 
				{

					std::string strName = furnituresLeft->GetName();
					strName = Scene::tolowerString(strName);
					if (ItemFromInput == strName) {
						furnituresLeft->InteractFurniture(player);
					}
					if (!checkValidInput)
						checkValidInput = (ItemFromInput == strName);
				}
				if (furnituresDown)
				{

					std::string strName = furnituresDown->GetName();
					strName = Scene::tolowerString(strName);
					if (ItemFromInput == strName) {
						furnituresDown->InteractFurniture(player);
					}
					if (!checkValidInput)
						checkValidInput = (ItemFromInput == strName);
				}
				if (furnituresRight) 
				{

					std::string strName = furnituresRight->GetName();
					strName = Scene::tolowerString(strName);
					if (ItemFromInput == strName) {
						furnituresRight->InteractFurniture(player);
					}
					if (!checkValidInput)
						checkValidInput = (ItemFromInput == strName);
				}
				if (!checkValidInput)
				{
					ui.PrintDialogue(Vector2(3, 3), "Unknown Object, Enter Valid Object name. ");
					EmptyDialogue = false;
				}
				else
					break;
			}
			else if (stringInput == "interact" || stringInput == "i") {
				//+ ToPrint
				ClearDialogue();
				ui.PrintDialogue(Vector2(3,2), "What do you want to interact with? Please Enter 'i / interact (space) ' <object name>");
				//ui.CreateText( "Interact with what? Enter 'interact <object name>'", Vector2(4, 2));
				EmptyDialogue = false;
				DisplayFurnituresAroundPlayer(Vector2(4, 3));
			}
			else if (stringInput == "e")
			{
				if (furnituresUp) 
				{

					if (furnituresUp->GetFurnitureType() == Furniture::BedRoomDoor || furnituresUp->GetFurnitureType() == Furniture::KitchenDoor
						|| furnituresUp->GetFurnitureType() == Furniture::StoreRoomDoor || furnituresUp->GetFurnitureType() == Furniture::ToiletDoor) {

						furnituresUp->InteractFurniture(player);
						break;

					}
				}

				if (furnituresRight)
				{

					if (furnituresRight->GetFurnitureType() == Furniture::BedRoomDoor || furnituresRight->GetFurnitureType() == Furniture::KitchenDoor
						|| furnituresRight->GetFurnitureType() == Furniture::StoreRoomDoor || furnituresRight->GetFurnitureType() == Furniture::ToiletDoor) {
						furnituresRight->InteractFurniture(player);
						break;
					}
				}

				if (furnituresLeft) 
				{

					if (furnituresLeft->GetFurnitureType() == Furniture::BedRoomDoor || furnituresLeft->GetFurnitureType() == Furniture::KitchenDoor
						|| furnituresLeft->GetFurnitureType() == Furniture::StoreRoomDoor || furnituresLeft->GetFurnitureType() == Furniture::ToiletDoor) {
						furnituresLeft->InteractFurniture(player);
						break;
					}
				}

				if (furnituresDown) 
				{

					if (furnituresDown->GetFurnitureType() == Furniture::BedRoomDoor || furnituresDown->GetFurnitureType() == Furniture::KitchenDoor
						|| furnituresDown->GetFurnitureType() == Furniture::StoreRoomDoor || furnituresDown->GetFurnitureType() == Furniture::ToiletDoor) {
						furnituresDown->InteractFurniture(player);
						break;
					}
				}
				if (furnituresUp)
					if (furnituresUp->GetFurnitureType() == Furniture::LivingRoomDoor || furnituresUp->GetFurnitureType() == Furniture::MainDoor) {
						furnituresUp->InteractFurniture(player);
						break;
					}
				if (furnituresDown)
					if (furnituresDown->GetFurnitureType() == Furniture::LivingRoomDoor || furnituresDown->GetFurnitureType() == Furniture::MainDoor) {
						furnituresDown->InteractFurniture(player);
						break;
					}

				if (furnituresLeft)
					if (furnituresLeft->GetFurnitureType() == Furniture::LivingRoomDoor || furnituresLeft->GetFurnitureType() == Furniture::MainDoor) {
						furnituresLeft->InteractFurniture(player);
						break;
					}

				if (furnituresRight)
					if (furnituresRight->GetFurnitureType() == Furniture::LivingRoomDoor || furnituresRight->GetFurnitureType() == Furniture::MainDoor)
					{
						furnituresRight->InteractFurniture(player);
						break;
					}
			}
			
			else if (KeywordFromInput == "use" && ItemFromInput != "") 
			{
				if(InteractionsMgr.UseItem(ItemFromInput,player))
					break;
				else
				{

					ClearDialogue();
					//ui.PrintDialogue(Vector2(3, 2), "'Use': use any item by entering 'use' <item name> 'on' <object name>.");
					ui.CreateText("'Use': use any item by entering 'use' <item name> 'on' <object name>.", Vector2(3, 2));
					//ui.PrintDialogue(Vector2(3, 3), " - if you want to use multiple items enter 'use' <item name> 'with'/'and' <item name> 'on' <object name>");
					ui.CreateText(" - if you want to use multiple items enter 'use' <item name> 'with'/'and' <item name> 'on' <object name>", Vector2(2, 3));
					EmptyDialogue = false;
				}

			}
			else if (stringInput == "use"|| stringInput == "u")
			{
				ClearDialogue(); 
				ui.PrintDialogue(Vector2(3, 2), "'Use': use any item by entering 'use' <item name> 'on' <object name>.");
				ui.CreateText("'Use': use any item by entering 'use' <item name> 'on' <object name>.", Vector2(	3, 2));
				ui.PrintDialogue( Vector2(3, 3), " - if you want to use multiple items enter 'use' <item name> 'with'/'and' <item name> 'on' <object name>");
				ui.CreateText(" - if you want to use multiple items enter 'use' <item name> 'with'/'and' <item name> 'on' <object name>", Vector2(2, 3));
				EmptyDialogue = false;

			}
			else if (stringInput == "show endings") {
				//Endings
				SceneManager::LoadScene("EndingScene");
			}
			else if (stringInput == "help") {

				ClearDialogue();
				
				ui.CreateText("'e': transition through rooms by doors", Vector2(4, 2));
				ui.CreateText("'Interact / i ': To trigger item interaction, use to figure out what object does by entering 'interact' or 'i' <Object name>", Vector2(4, 3));
				ui.CreateText("'Move / m ': Allow your character to move after entering '/'.", Vector2(4, 4));
				ui.CreateText("'Use / u': use any item by entering 'use' <item name> 'on' <object name>.", Vector2(4, 5));
				ui.CreateText(" - if you want to use multiple items enter 'use' <item name> 'with'/'and' <item name> 'on' <object name>", Vector2(4, 6));
				ui.CreateText("Press 'Enter' again to move. ", Vector2(4, 7));

				EmptyDialogue = false;
			}
			else if (stringInput == "move"|| stringInput == "m")
			{
				break;
			}
			else {
				ClearDialogue(); 
				ui.CreateText("Invalid input, Enter 'help' for commands. ", Vector2(3, 2));
				EmptyDialogue = false; 
			}

		}
		ClearDialogue();

		ui.CreateText("[ (W)(A)(S)(D): Move                                  ]", Vector2(10, 0));
		break;

	}
}

std::string GameManager::InputField(void)
{
	Scene::GotoXY(Application::numberOfColumns / 2 - 81, 45);
	const int MAX_LENGTH = 50;
	std::string input{};
	char ch{};

	Application::ShowCursor();
	std::string text = "Input: ";
	std::cout << text;
	while (true) {
		ch = GameManager::_getch(); // Get a single character input without echoing to the console

		// Check if the Enter key is pressed
		if (ch == '\r') {
			
			break; // Stop input on Enter key
		}
		if ((ch == ' ' && input.length() == 0))
			continue;
		if (input.length() > 0)
			if ((input[input.length() - 1] == ' ' && ch == ' '))
				continue;
		// Allow Backspace
		if (ch == '\b' && !input.empty()) {
			std::cout << "\b \b"; // Erase the last character from the console
			input.pop_back();     // Remove the last character from the input
		}
		// Restrict the number of characters
		else if (input.length() < MAX_LENGTH && ch != '\b' && ch != '\t') {
			input += ch;          // Add character to input
			std::cout << ch;      // Display the character
		}
	}
	Application::HideCursor();

	Scene::GotoXY(Application::numberOfColumns / 2 - 81, 45);
	for (char& chtr : input + text)
		std::cout << ' ';

	return input;
}

bool GameManager::GetGameEnded() const
{
	return GameEnded;
}
bool GameManager::GetGameWon() const
{
	return GameWon;
}

void GameManager::DisplayFurnituresAroundPlayer(Vector2 printAtPos)
{

	UI ui(Vector2(Application::numberOfColumns / 2 - 171 / 2, 35), 0, 171); 

	Furniture* furnituresLeft, * furnituresRight, * furnituresUp, * furnituresDown;
	furnituresLeft = dynamic_cast<Furniture*>(SceneManager::currentScene->GetObjectManager()->GetObjectAtPosition(Vector2(player->GetPosition()->GetX() - 1, player->GetPosition()->GetY())));
	furnituresRight = dynamic_cast<Furniture*>(SceneManager::currentScene->GetObjectManager()->GetObjectAtPosition(Vector2(player->GetPosition()->GetX() + 1, player->GetPosition()->GetY())));
	furnituresUp = dynamic_cast<Furniture*>(SceneManager::currentScene->GetObjectManager()->GetObjectAtPosition(Vector2(player->GetPosition()->GetX(), player->GetPosition()->GetY() - 1)));
	furnituresDown = dynamic_cast<Furniture*>(SceneManager::currentScene->GetObjectManager()->GetObjectAtPosition(Vector2(player->GetPosition()->GetX(), player->GetPosition()->GetY() + 1)));

	Furniture*** lists = new Furniture * *[4];
	lists[0] = &furnituresLeft;
	lists[1] = &furnituresRight;
	lists[2] = &furnituresUp;
	lists[3] = &furnituresDown;
	int loopCount;
	for (int i = 0; i < 4; i++)
	{
		loopCount = 0;

		for (int x = i + 1; loopCount < 3; loopCount++)
		{
			if (x >= 4)
				x = 0;
			if (*lists[i] && *lists[x]) {
				if ((*lists[i])->GetName() == (*lists[x])->GetName()) {
					*lists[x] = nullptr;
				}
			}
			x++;
		}


	}
	delete[] lists; ui.CreateText("Objects around you.", (Vector2(printAtPos.GetX(), printAtPos.GetY())));
	int count = 0;
	if (furnituresLeft) {
		count++; 
		//ui.PrintDialogue(Vector2(printAtPos.GetX(), printAtPos.GetY() + count), furnituresLeft->GetName());
		ui.CreateText("  - " + furnituresLeft->GetName(), (Vector2(printAtPos.GetX(), printAtPos.GetY() + count)));
	}
	if (furnituresUp) {
		count++;
		ui.CreateText("  - " + furnituresUp->GetName(), (Vector2(printAtPos.GetX(), printAtPos.GetY() + count)));
	}
	if (furnituresRight) {
		count++;
		ui.CreateText("  - " + furnituresRight->GetName(), (Vector2(printAtPos.GetX(), printAtPos.GetY() + count)));

	}
	if (furnituresDown) { 
		count++;
		ui.CreateText("  - " + furnituresDown->GetName(), (Vector2(printAtPos.GetX(), printAtPos.GetY() + count)));
	}
}

void GameManager::CreatePlayer(Vector2 toPos)
{
	if (player)
		player = nullptr;
	player = new Player();
	if (SceneManager::prevScene == "BedroomScene")
		toPos = Vector2(8, 1);
	if (SceneManager::prevScene == "StoreRoomScene")
		toPos = Vector2(1, 3);

	if (SceneManager::prevScene == "ToiletScene")
		toPos = Vector2(9, 6);
	if (SceneManager::prevScene == "KitchenScene")
		toPos = Vector2(11, 2);
	*player->GetPosition() = toPos;
}

void GameManager::ClearDialogue()
{
	EmptyDialogue = true;
	UI ui(Vector2(Application::numberOfColumns / 2 - 167 / 2, 35), 0, 169);
	std::string clearDialogue;
	for (int i = 0; i < 166; i++)
	{
		clearDialogue += ' ';
	}
	for (int h = 1; h < 12; h++)
	{
		ui.CreateText(clearDialogue, Vector2(0, h));

	}
}

char GameManager::_getch(void)
{
	char ch = 0;
	DWORD mode, count;
	HANDLE h = GetStdHandle(STD_INPUT_HANDLE);

	GetConsoleMode(h, &mode);
	SetConsoleMode(h, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

	ReadConsoleA(h, &ch, 1, &count, NULL);

	SetConsoleMode(h, mode);
	return tolower(ch);
}



