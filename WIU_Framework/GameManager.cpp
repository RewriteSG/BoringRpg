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

GameManager::GameManager() : gameUI(nullptr)
{
	whatScenePlayerIn = "";
	GM_Instance = this;
	//Weapon = nullptr;
	//robber = nullptr;
	GameEnded = false;
	GameWon = true;
	player = nullptr;
	//robberDown = false;
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
	gameUI = new UI(Vector2(130, 12), 7);
	InteractionsMgr.Start();
}
void GameManager::Update()
{
	inventory.DisplayItems();
	if (TimeSys.TimeTaken >= TimeSys.RobberTime)
	{
		whatScenePlayerIn = SceneManager::currentScene->getName();
		ending.Update();
	}
	else
		HandleInput();
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
	if (player == nullptr)
		return;
	Furniture* furnituresLeft, * furnituresRight, * furnituresUp, * furnituresDown;
	furnituresLeft = dynamic_cast<Furniture*>(SceneManager::currentScene->GetObjectManager()->GetObjectAtPosition(Vector2(player->GetPosition()->GetX() - 1, player->GetPosition()->GetY())));
	furnituresRight = dynamic_cast<Furniture*>(SceneManager::currentScene->GetObjectManager()->GetObjectAtPosition(Vector2(player->GetPosition()->GetX() + 1, player->GetPosition()->GetY())));
	furnituresUp = dynamic_cast<Furniture*>(SceneManager::currentScene->GetObjectManager()->GetObjectAtPosition(Vector2(player->GetPosition()->GetX(), player->GetPosition()->GetY() - 1)));
	furnituresDown = dynamic_cast<Furniture*>(SceneManager::currentScene->GetObjectManager()->GetObjectAtPosition(Vector2(player->GetPosition()->GetX(), player->GetPosition()->GetY() + 1)));
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
		ToPrint = "There is nothing around the player.";

	ClearDialogue();
	UI ui(Vector2(Application::numberOfColumns / 2 - 171 / 2, 35), 0, 171);
	ui.CreateText(ToPrint, Vector2(2, 2));
	char input = _getch();

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
		

		while (true) {

			ui.CreateText(" Options: Enter, Exit, Interact, Move.  ", Vector2(10, 0));
			ClearDialogue(); 
		InvalidInput:

			ui.CreateText(ToPrint, Vector2(2, 2));
			string stringInput = InputField();
			string ItemFromInput = "";
			string KeywordFromInput = "";
			//move for doors only
			
			bool showHelp = false;
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
			if (KeywordFromInput == "interact" && ItemFromInput != "") 
			{
				bool checkValidInput = false; 
				if (furnituresUp) {

					std::string strName = furnituresUp->GetName();
					strName = Scene::tolowerString(strName);
					if (ItemFromInput == strName) {
						furnituresUp->InteractFurniture(player);
					}
					if (!checkValidInput)
						checkValidInput = (ItemFromInput == strName);
				}
				if (furnituresLeft) {

					std::string strName = furnituresLeft->GetName();
					strName = Scene::tolowerString(strName);
					if (ItemFromInput == strName) {
						furnituresLeft->InteractFurniture(player);
					}
					if (!checkValidInput)
						checkValidInput = (ItemFromInput == strName);
				}
				if (furnituresDown) {

					std::string strName = furnituresDown->GetName();
					strName = Scene::tolowerString(strName);
					if (ItemFromInput == strName) {
						furnituresDown->InteractFurniture(player);
					}
					if (!checkValidInput)
						checkValidInput = (ItemFromInput == strName);
				}
				if (furnituresRight) {

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
					ui.CreateText("Unknown Object, Enter Valid Object name. ", Vector2(2, 3));
					goto InvalidInput;
				}
			}else
		    if (stringInput == "interact") {
				//+ ToPrint

				ui.CreateText("Interact with what? Enter 'interact <object name>'" , Vector2(2,3));
				goto InvalidInput;
			}
			else if (stringInput == "enter") 
			{
				if (furnituresUp) {

					if (furnituresUp->GetFurnitureType() == Furniture::BedRoomDoor || furnituresUp->GetFurnitureType() == Furniture::KitchenDoor
						|| furnituresUp->GetFurnitureType() == Furniture::StoreRoomDoor || furnituresUp->GetFurnitureType() == Furniture::ToiletDoor) {

						furnituresUp->InteractFurniture(player);
					}
				}

				if (furnituresRight) {

					if (furnituresRight->GetFurnitureType() == Furniture::BedRoomDoor || furnituresRight->GetFurnitureType() == Furniture::KitchenDoor
						|| furnituresRight->GetFurnitureType() == Furniture::StoreRoomDoor || furnituresRight->GetFurnitureType() == Furniture::ToiletDoor)
						furnituresRight->InteractFurniture(player);
				}

				if (furnituresLeft) {

					if (furnituresLeft->GetFurnitureType() == Furniture::BedRoomDoor || furnituresLeft->GetFurnitureType() == Furniture::KitchenDoor
						|| furnituresLeft->GetFurnitureType() == Furniture::StoreRoomDoor || furnituresLeft->GetFurnitureType() == Furniture::ToiletDoor)
						furnituresLeft->InteractFurniture(player);
				}

				if (furnituresDown) {

					if (furnituresDown->GetFurnitureType() == Furniture::BedRoomDoor || furnituresDown->GetFurnitureType() == Furniture::KitchenDoor
						|| furnituresDown->GetFurnitureType() == Furniture::StoreRoomDoor || furnituresDown->GetFurnitureType() == Furniture::ToiletDoor)
						furnituresDown->InteractFurniture(player);
				}

			}
			else if (stringInput == "exit") {

				if (furnituresUp)
					if (furnituresUp->GetFurnitureType() == Furniture::LivingRoomDoor || furnituresUp->GetFurnitureType() == Furniture::MainDoor)
						furnituresUp->InteractFurniture(player);

				if (furnituresDown)
					if (furnituresDown->GetFurnitureType() == Furniture::LivingRoomDoor || furnituresDown->GetFurnitureType() == Furniture::MainDoor)
						furnituresDown->InteractFurniture(player);

				if (furnituresLeft)
					if (furnituresLeft->GetFurnitureType() == Furniture::LivingRoomDoor || furnituresLeft->GetFurnitureType() == Furniture::MainDoor)
						furnituresLeft->InteractFurniture(player);

				if (furnituresRight)
					if (furnituresRight->GetFurnitureType() == Furniture::LivingRoomDoor || furnituresRight->GetFurnitureType() == Furniture::MainDoor)
						furnituresRight->InteractFurniture(player);

			}
			
			else if (stringInput == "show endings") {
				//Endings
				SceneManager::LoadScene("EndingScene");
			}
			else if (stringInput == "move")
			{
				break;
			}
			
			else {
				ui.CreateText("Invalid input", Vector2(2, 3));
				goto InvalidInput;
			}

			break;
		}
	}
	//LivingRoomScene* livingRoom = dynamic_cast<LivingRoomScene*>(SceneManager::currentScene);
	//if (livingRoom)
	//{
	//	gameUI->CreateOptionUI(Vector2(-2, 13), false);
	//	gameUI->GetOptionUI()->AddOption(new std::string("g"));
	//	gameUI->GetOptionUI()->AddOption(new std::string("h"));
	//	int chooseItem = gameUI->PickDialogue(Vector2(-2, 19), "Choose one?");
	//	//if(chooseItem == 0)
	//}

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
	UI ui(Vector2(Application::numberOfColumns / 2 - 171 / 2, 35), 0, 171);
	std::string clearDialogue;
	for (int i = 0; i < 169; i++)
	{
		clearDialogue += ' ';
	}
	for (int h = 1; h < 12; h++)
	{
		ui.CreateText(clearDialogue, Vector2(1, h));

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



