#include "GameManager.h"
#include "Scene.h"
#include "MyFunctions.cpp"
#include "Application.h"
#include "Windows.h"
#include "SceneManager.h"
#include "MainMenu.h"
using namespace myFunctions;

GameManager* GameManager::GM_Instance = nullptr;

GameManager::GameManager()
{
	GM_Instance = this;
	//Weapon = nullptr;
	GameEnded = false;
	GameWon = true;
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
}
void GameManager::Update()
{
	GameEnded = false;
	MainMenu* menu = dynamic_cast<MainMenu*>(SceneManager::currentScene);
	if (menu)
		return;
	PromptInput();
	HandleInput();
	
}
void GameManager::Exit()
{

}

void GameManager::PromptInput()
{
	Scene::GotoXY(110, 12);
	cout << "Input:                                                        ";
	Scene::GotoXY(117, 12);
}
void GameManager::HandleInput(void)
{
	char input = _getch();

	switch (input)
	{
	case 'w':
		//Move up
		break;
	case 's':
		//Move down
		break;
	case 'd':
		//Move right
		break;
	case 'a':
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



