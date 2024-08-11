#include "GameManager.h"
#include "Scene.h"
#include "MyFunctions.cpp"

using namespace myFunctions;

GameManager* GameManager::GM_Instance = nullptr;

GameManager::GameManager()
{
	GM_Instance = this;
	//Weapon = nullptr;
	GameEnded = false;
	GameWon = true;
}

void GameManager::Start()
{

	GM_Instance = this;
	//Weapon = nullptr;
	GameEnded = false;
	GameWon = true;
	
	//new Entity(Vector2(4, 4));
}

//
//Application::GotoXY(14 + (10), 2);
//if (weaponHeld)
//{
//	cout << "Player Health (" << GetHealth() << ") Attack ("
//		<< GetAttackDamage() - weaponHeld->GetDamageIncrease() << "+" << weaponHeld->GetDamageIncrease() << ")";
//
//}
//else
//cout << "Player Health (" << GetHealth() << ") Attack (" << GetAttackDamage() << ")";
void GameManager::Update()
{
	GameEnded = false;

	PromptInput();

	string input;
	cin >> input;
	Scene::LowerString(input);

	HandleInput(input[0]);
	
}

void GameManager::HandleInput(char input)
{

}
bool GameManager::GetGameEnded() const
{
	return GameEnded;
}
bool GameManager::GetGameWon() const
{
	return GameWon;
}

GameManager* GameManager::getGM()
{
	return GM_Instance;
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
