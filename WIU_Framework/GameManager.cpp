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



