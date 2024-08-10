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
	turns = 0; goblinCount = 0;
	GameEnded = false;
	GameWon = true;
}

void GameManager::Start()
{

	GM_Instance = this;
	//Weapon = nullptr;
	turns = 0; goblinCount = 0;
	GameEnded = false;
	GameWon = true;

	string clearInput = "";
	for (int i = 0; i < 999; i++)
	{
		clearInput += " ";
	}
	system("cls");
	int input = 0;
	Scene::GotoXY(0, 1);
	cout << "Pick a Character! \n 1 - Archer\n 2 - Barbarian \n Input: ";
	while (!(cin >> input) && (input != 1 && input != 2)) 
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		Scene::GotoXY(0, 1);
		cout << "Pick a Character! \n 1 - Archer\n 2 - Barbarian \n Input: ";
		cout << clearInput;
		Scene::GotoXY(8, 4);

	}

	turns = 0;

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
	cout << "Player Option Move (W)(A)(S)(D) Attack(I)(J)(K)(L) \n Input:                                                        ";
	Scene::GotoXY(7, 13);
}
