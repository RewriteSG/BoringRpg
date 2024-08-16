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
using namespace myFunctions;

GameManager* GameManager::GM_Instance = nullptr;

GameManager::GameManager() : gameUI(nullptr)
{
	GM_Instance = this;
	//Weapon = nullptr;
	robber = nullptr;
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

	/*
	if (robberDown) 
	{

	}*/
		//return;
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



