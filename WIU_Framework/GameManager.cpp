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
#include "Furniture.h"
using namespace myFunctions;

GameManager* GameManager::GM_Instance = nullptr;

GameManager::GameManager() : gameUI(nullptr)
{
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
		typeofFurniture = furnituresLeft->GetFurnitureType();
		switch (typeofFurniture)
		{
		case Furniture::SofaKey:
			ToPrint += "Sofa";
			break;
		case Furniture::Clock:
			ToPrint += "Clock";
			break;
		case Furniture::EmptySofa:
			ToPrint += "Sofa";
			break;
		case Furniture::BedroomCabinet1:
			ToPrint += "Cabinet";
			break;
		case Furniture::BedroomCabinet2:
			ToPrint += "Cabinet";
			break;
		case Furniture::LivingRoomCabinet:
			ToPrint += "Cabinet";
			break;
		case Furniture::Television:
			ToPrint += "Television";
			break;
		case Furniture::KitchenCabinet:
			ToPrint += "Cabinet";
			break;
		case Furniture::Sink:
			ToPrint += "Sink";
			break;
		case Furniture::Planks:
			ToPrint += "Planks";
			break;
		case Furniture::Door:
			ToPrint += "Door";
			break;
		case Furniture::BedRoomDoor:
			ToPrint += "Door";
			break;
		case Furniture::ToiletBowl:
			ToPrint += "Toilet Bowl";
			break;
		case Furniture::ShowerArea:
			ToPrint += "Shower";
			break;
		case Furniture::ToiletCabinet:
			ToPrint += "Cabinet";
			break;
		case Furniture::ToiletDoor:
			ToPrint += "Door";
			break;
		case Furniture::StoreRoomDoor:
			ToPrint += "Door";
			break;
		case Furniture::CardBoardBox:
			ToPrint += furnituresLeft->GetName();
			break;
		case Furniture::LivingroomTable:
			ToPrint += "Table";
			break;
		case Furniture::Bedroomtable:
			ToPrint += "Table";
			break;
		case Furniture::Phone:
			ToPrint += "Phone";
			break;
		case Furniture::ToolBox:
			ToPrint += "Toolbox";
			break;
		case Furniture::Stove:
			ToPrint += "Stove";
			break;
		case Furniture::Bed:
			ToPrint += "Bed";
			break;
		case Furniture::TrashCan:
			ToPrint += "Trash Can";
			break;
		case Furniture::LivingRoomDoor:
			ToPrint += "Door";
			break;
		case Furniture::EmptyBoxType1:
			ToPrint += furnituresLeft->GetName();
			break;
		case Furniture::EmptyBoxType2:
			ToPrint += furnituresLeft->GetName();
			break;
		case Furniture::Box:
			ToPrint += furnituresLeft->GetName();
			break;
		case Furniture::Fridge:
			ToPrint += "Fridge";
			break;
		case Furniture::sink:
			ToPrint += "Sink";
			break;
		case Furniture::KitchenTable:
			ToPrint += "Table";
			break;
		case Furniture::KitchenDoor:
			ToPrint += "Door";
			break;
		default:
			break;
		}
	}
	if (furnituresRight)
	{
		if (furnituresLeft)
			ToPrint += " and a ";
		typeofFurniture = furnituresRight->GetFurnitureType();
		switch (typeofFurniture)
		{
		case Furniture::SofaKey:
			ToPrint += "Sofa";
			break;
		case Furniture::Clock:
			ToPrint += "Clock";
			break;
		case Furniture::EmptySofa:
			ToPrint += "Sofa";
			break;
		case Furniture::BedroomCabinet1:
			ToPrint += "Cabinet";
			break;
		case Furniture::BedroomCabinet2:
			ToPrint += "Cabinet";
			break;
		case Furniture::LivingRoomCabinet:
			ToPrint += "Cabinet";
			break;
		case Furniture::Television:
			ToPrint += "Television";
			break;
		case Furniture::KitchenCabinet:
			ToPrint += "Cabinet";
			break;
		case Furniture::Sink:
			ToPrint += "Sink";
			break;
		case Furniture::Planks:
			ToPrint += "Planks";
			break;
		case Furniture::Door:
			ToPrint += "Door";
			break;
		case Furniture::BedRoomDoor:
			ToPrint += "Door";
			break;
		case Furniture::ToiletBowl:
			ToPrint += "Toilet Bowl";
			break;
		case Furniture::ShowerArea:
			ToPrint += "Shower";
			break;
		case Furniture::ToiletCabinet:
			ToPrint += "Cabinet";
			break;
		case Furniture::ToiletDoor:
			ToPrint += "Door";
			break;
		case Furniture::StoreRoomDoor:
			ToPrint += "Door";
			break;
		case Furniture::CardBoardBox:
			ToPrint += furnituresRight->GetName();
			break;
		case Furniture::LivingroomTable:
			ToPrint += "Table";
			break;
		case Furniture::Bedroomtable:
			ToPrint += "Table";
			break;
		case Furniture::Phone:
			ToPrint += "Phone";
			break;
		case Furniture::ToolBox:
			ToPrint += "Toolbox";
			break;
		case Furniture::Stove:
			ToPrint += "Stove";
			break;
		case Furniture::Bed:
			ToPrint += "Bed";
			break;
		case Furniture::TrashCan:
			ToPrint += "Trash Can";
			break;
		case Furniture::LivingRoomDoor:
			ToPrint += "Door";
			break;
		case Furniture::EmptyBoxType1:
			ToPrint += furnituresRight->GetName();
			break;
		case Furniture::EmptyBoxType2:
			ToPrint += furnituresRight->GetName();
			break;
		case Furniture::Box:
			ToPrint += furnituresRight->GetName();
			break;
		case Furniture::Fridge:
			ToPrint += "Fridge";
			break;
		case Furniture::sink:
			ToPrint += "Sink";
			break;
		case Furniture::KitchenTable:
			ToPrint += "Table";
			break;
		case Furniture::KitchenDoor:
			ToPrint += "Door";
			break;
		default:
			break;
		}
	}
	if (furnituresUp)
	{
		if (furnituresLeft || furnituresRight)
			ToPrint += " and a ";
		typeofFurniture = furnituresUp->GetFurnitureType();
		switch (typeofFurniture)
		{
		case Furniture::SofaKey:
			ToPrint += "Sofa";
			break;
		case Furniture::Clock:
			ToPrint += "Clock";
			break;
		case Furniture::EmptySofa:
			ToPrint += "Sofa";
			break;
		case Furniture::BedroomCabinet1:
			ToPrint += "Cabinet";
			break;
		case Furniture::BedroomCabinet2:
			ToPrint += "Cabinet";
			break;
		case Furniture::LivingRoomCabinet:
			ToPrint += "Cabinet";
			break;
		case Furniture::Television:
			ToPrint += "Television";
			break;
		case Furniture::KitchenCabinet:
			ToPrint += "Cabinet";
			break;
		case Furniture::Sink:
			ToPrint += "Sink";
			break;
		case Furniture::Planks:
			ToPrint += "Planks";
			break;
		case Furniture::Door:
			ToPrint += "Door";
			break;
		case Furniture::BedRoomDoor:
			ToPrint += "Door";
			break;
		case Furniture::ToiletBowl:
			ToPrint += "Toilet Bowl";
			break;
		case Furniture::ShowerArea:
			ToPrint += "Shower";
			break;
		case Furniture::ToiletCabinet:
			ToPrint += "Cabinet";
			break;
		case Furniture::ToiletDoor:
			ToPrint += "Door";
			break;
		case Furniture::StoreRoomDoor:
			ToPrint += "Door";
			break;
		case Furniture::CardBoardBox:
			ToPrint += furnituresUp->GetName();
			break;
		case Furniture::LivingroomTable:
			ToPrint += "Table";
			break;
		case Furniture::Bedroomtable:
			ToPrint += "Table";
			break;
		case Furniture::Phone:
			ToPrint += "Phone";
			break;
		case Furniture::ToolBox:
			ToPrint += "Toolbox";
			break;
		case Furniture::Stove:
			ToPrint += "Stove";
			break;
		case Furniture::Bed:
			ToPrint += "Bed";
			break;
		case Furniture::TrashCan:
			ToPrint += "Trash Can";
			break;
		case Furniture::LivingRoomDoor:
			ToPrint += "Door";
			break;
		case Furniture::EmptyBoxType1:
			ToPrint += furnituresUp->GetName();
			break;
		case Furniture::EmptyBoxType2:
			ToPrint += furnituresUp->GetName();
			break;
		case Furniture::Box:
			ToPrint += furnituresUp->GetName();
			break;
		case Furniture::Fridge:
			ToPrint += "Fridge";
			break;
		case Furniture::sink:
			ToPrint += "Sink";
			break;
		case Furniture::KitchenTable:
			ToPrint += "Table";
			break;
		case Furniture::KitchenDoor:
			ToPrint += "Door";
			break;
		default:
			break;
		}
	}
	if (furnituresDown)
	{

		if (furnituresLeft || furnituresRight || furnituresUp)
			ToPrint += " and a ";
		typeofFurniture = furnituresDown->GetFurnitureType();
		switch (typeofFurniture)
		{
		case Furniture::SofaKey:
			ToPrint += "Sofa";
			break;
		case Furniture::Clock:
			ToPrint += "Clock";
			break;
		case Furniture::EmptySofa:
			ToPrint += "Sofa";
			break;
		case Furniture::BedroomCabinet1:
			ToPrint += "Cabinet";
			break;
		case Furniture::BedroomCabinet2:
			ToPrint += "Cabinet";
			break;
		case Furniture::LivingRoomCabinet:
			ToPrint += "Cabinet";
			break;
		case Furniture::Television:
			ToPrint += "Television";
			break;
		case Furniture::KitchenCabinet:
			ToPrint += "Cabinet";
			break;
		case Furniture::Sink:
			ToPrint += "Sink";
			break;
		case Furniture::Planks:
			ToPrint += "Planks";
			break;
		case Furniture::Door:
			ToPrint += "Door";
			break;
		case Furniture::BedRoomDoor:
			ToPrint += "Door";
			break;
		case Furniture::ToiletBowl:
			ToPrint += "Toilet Bowl";
			break;
		case Furniture::ShowerArea:
			ToPrint += "Shower";
			break;
		case Furniture::ToiletCabinet:
			ToPrint += "Cabinet";
			break;
		case Furniture::ToiletDoor:
			ToPrint += "Door";
			break;
		case Furniture::StoreRoomDoor:
			ToPrint += "Door";
			break;
		case Furniture::CardBoardBox:
			ToPrint += furnituresDown->GetName();
			break;
		case Furniture::LivingroomTable:
			ToPrint += "Table";
			break;
		case Furniture::Bedroomtable:
			ToPrint += "Table";
			break;
		case Furniture::Phone:
			ToPrint += "Phone";
			break;
		case Furniture::ToolBox:
			ToPrint += "Toolbox";
			break;
		case Furniture::Stove:
			ToPrint += "Stove";
			break;
		case Furniture::Bed:
			ToPrint += "Bed";
			break;
		case Furniture::TrashCan:
			ToPrint += "Trash Can";
			break;
		case Furniture::LivingRoomDoor:
			ToPrint += "Door";
			break;
		case Furniture::EmptyBoxType1:
			ToPrint += furnituresDown->GetName();
			break;
		case Furniture::EmptyBoxType2:
			ToPrint += furnituresDown->GetName();
			break;
		case Furniture::Box:
			ToPrint += furnituresDown->GetName();
			break;
		case Furniture::Fridge:
			ToPrint += "Fridge";
			break;
		case Furniture::sink:
			ToPrint += "Sink";
			break;
		case Furniture::KitchenTable:
			ToPrint += "Table";
			break;
		case Furniture::KitchenDoor:
			ToPrint += "Door";
			break;
		default:
			break;
		}
	}
	if (ToPrint != "blank")
		ToPrint += " next to you.";
	else
		ToPrint = "There is nothing around the player.";

	gameUI->CreateText("                                                           ", Vector2(-94, 24));
	gameUI->CreateText(ToPrint, Vector2(-94, 24));

	char input = _getch();

	switch (input)
	{
	case 'w':
		//Move up
		*player->GetPosition() += Vector2(0, -1);
		break;
	case 's':
		*player->GetPosition() += Vector2(0, 1);
		//Move down
		break;
	case 'd':
		*player->GetPosition() += Vector2(1, 0);
		//Move right
		break;
	case 'a':
		*player->GetPosition() += Vector2(-1, 0);
		//Move left
		break;
	case '/':
		InputField();
		break;
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

		// Allow Backspace
		if (ch == '\b' && !input.empty()) {
			std::cout << "\b \b"; // Erase the last character from the console
			input.pop_back();     // Remove the last character from the input
		}
		// Restrict the number of characters
		else if (input.length() < MAX_LENGTH && ch != '\b') {
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
		toPos = Vector2(10, 6);
	*player->GetPosition() = toPos;
}
void GameManager::CreateRobber(Vector2 toPos)
{
	if (robber)
		robber = nullptr;
	robber = new Robber();
//
	if (SceneManager::prevScene == "BedroomScene")
	{
		toPos = Vector2(8, 1);
	}
	
	*robber->GetPosition() = toPos;
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



