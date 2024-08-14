#include "GameManager.h"
#include "Scene.h"
#include "MyFunctions.cpp"
#include "Application.h"
#include "Windows.h"
#include "SceneManager.h"
#include "MainMenu.h"
#include "Player.h"
#include "conio.h"
using namespace myFunctions;

GameManager* GameManager::GM_Instance = nullptr;

GameManager::GameManager() : gameUI(nullptr)
{
	GM_Instance = this;
	//Weapon = nullptr;
	GameEnded = false;
	GameWon = true;
	player = nullptr;
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
	gameUI->CreateOptionUI(Vector2(1, 19), false);
	gameUI->GetOptionUI()->AddOption(new std::string(Player::playerInstance->GetName()));
	gameUI->GetOptionUI()->AddOption(new std::string("Pan"));
	gameUI->GetOptionUI()->AddOption(new std::string("Blank"));
}
void GameManager::Update()
{
	gameUI->PickDialogue(Vector2(1, 19), "Pick one please");
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
		delete player;
	player = new Player();
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



