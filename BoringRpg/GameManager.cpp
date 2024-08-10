#include "GameManager.h"
#include "Scene.h"
#include "MyFunctions.cpp"

using namespace myFunctions;

GameManager* GameManager::GM_Instance = nullptr;

GameManager::GameManager()
{
	GM_Instance = this;
	isPlayerTurn = true;
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

	Scene::GotoXY(0, 0);
	cout << "-----Boring RPG-----";
	for (int i = 0; i < 20; i++)
	{

		Scene::GotoXY(i, 1);
		cout << "                                            ";
	}
	for (int i = 2; i < 12; i++)
	{

		Scene::GotoXY(0, i);
		cout << "+";
	}
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
	GameEnded = false;PromptInput();


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
	isPlayerTurn = true;
	Scene::GotoXY(0, 12);
	cout << "Input:                                                        ";
	Scene::GotoXY(7, 12);
}
