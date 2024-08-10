#include "GameManager.h"
#include "Scene.h"
#include "MyFunctions.cpp"
#include "Barbarian.h"

#include "HealingGlobe.h"
#include "Weapon.h"
#include "Archer.h"
using namespace myFunctions;

GameManager* GameManager::GM_Instance = nullptr;

GameManager::GameManager()
{
	GM_Instance = this;
	Player = nullptr;
	isPlayerTurn = true;
	Goblins = nullptr;
	HealthGlobes = nullptr;
	//Weapon = nullptr;
	turns = 0; goblinCount = 0;
	GameEnded = false;
	GameWon = true;
}

void GameManager::Start()
{

	GM_Instance = this;
	Player = nullptr;
	isPlayerTurn = true;
	Goblins = nullptr;
	HealthGlobes = nullptr;
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
	if (input == 2)
		Player = new Barbarian();
	else 	
		Player = new Archer();

	int randomNumberX = 0;
	int randomNumberY = 0;
	for (int i = 0; i < 3; i++)
	{
		randomNumberX = (rand() % 10);
		randomNumberY = (rand() % 10);
		if (randomNumberX == 0 && randomNumberY == 0)
			randomNumberX++;
		Goblins = ArrayAdd(Goblins, new Goblin(Vector2(randomNumberX, randomNumberY), i + 1), goblinCount);
	}
	for (int i = 0; i < 2; i++)
	{
		randomNumberX = (rand() % 10);
		randomNumberY = (rand() % 10);

		if (randomNumberX == 0 && randomNumberY == 0)
			randomNumberX++;
		new HealingGlobe(Vector2(randomNumberX, randomNumberY), i+1); 
	}

	randomNumberX = (rand() % 10);
	randomNumberY = (rand() % 10);

	if (randomNumberX == 0 && randomNumberY == 0)
		randomNumberX++;
	new Weapon(Vector2(randomNumberX, randomNumberY), 1);

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
	GameEnded = (!Player || isAllGoblinsDead());
	if (GameEnded) {

		GameWon = isAllGoblinsDead();

		return;
	}
	GameObject** objects = ObjectManager::getObjectManager()->GetObjects();
	int objectsCount = ObjectManager::getObjectManager()->GetObjectsCount();
	for (int y = 0;  y < 20;  y++)
	{
		Scene::GotoXY(14 + (10), 2 + y);
		cout << "                                                          ";
	}
	Goblin* gob;
	HealingGlobe* healingGlobe; Weapon* weapon;
	Scene::GotoXY(14 + (10), 2);
	Weapon* weaponHeld = Player->GetWeaponHeld();
	if (weaponHeld)
	{
		cout << "Player Row ("<< Player->GetPosition()->GetY() << ") Col (" << Player->GetPosition()->GetX() << ") Health (" << Player->GetHealth() << ") Attack ("
			<< Player->GetAttackDamage() - weaponHeld->GetDamageIncrease() << "+" << weaponHeld->GetDamageIncrease() << ")";

	}
	else
		cout << "Player Row (" << Player->GetPosition()->GetY() << ") Col (" << Player->GetPosition()->GetX() << ") Health (" << Player->GetHealth() << ") Attack ("
		<< Player->GetAttackDamage() << ")";
	for (int i = 1; i < objectsCount; i++)
	{
		Scene::GotoXY(14 + (10), 2 + i);
		gob = dynamic_cast<Goblin*>(objects[i]);
		if (gob) 
		{
			cout << "Goblin" << gob->GetObjectChar() << " Row(" << gob->GetPosition()->GetY() << ") Col(" << gob->GetPosition()->GetX() << ")" << " Health (" << gob->GetHealth() << ") Attack (" << gob->GetAttackDamage() << ")";
			continue;
		}
		healingGlobe = dynamic_cast<HealingGlobe*>(objects[i]);
		if (healingGlobe)
		{
			cout << "HealingGlobe" << healingGlobe->GetID()<< " Row(" << healingGlobe->GetPosition()->GetY() << ") Col(" << healingGlobe->GetPosition()->GetX() << ")";
			continue;
		}
		weapon = dynamic_cast<Weapon*>(objects[i]);
		if (weapon && weapon->GetActive()) 
		{
			
			cout << "Weapon" << weapon->GetID() << " Row(" << weapon->GetPosition()->GetY() << ") Col(" << weapon->GetPosition()->GetX() << ")";
			continue;
		}
	}
	PromptInput();


	string input;
	cin >> input;
	Scene::LowerString(input);

	HandleInput(input[0]);
	
}

void GameManager::HandleInput(char input)
{
	Vector2 dir;
	bool isMoving = false;
	bool invalidInput = false;


	isPlayerTurn = false;
	switch (input)
	{
	case 'w':
	case 'a':
	case 's':
	case 'd':
		isMoving = true;
		break;
	default:
		isMoving = false;
		break;
	}
	switch (input)
	{
	case 'w':
	case 'i':
		dir.SetXandY(0, -1);
		break;
	case 'a':
	case 'j':
		dir.SetXandY(-1, 0);
		break;
	case 's':
	case 'k':
		dir.SetXandY(0, 1);
		break;
	case 'd':
	case 'l':
		dir.SetXandY(1, 0);
		break;
	default:
		invalidInput = true;
		isPlayerTurn = true; 
		break;

	}
	if (invalidInput)
		return;
	
	if (isMoving)
		*Player->GetPosition() += dir;
	else 
	{
		//dir += *Player->GetPosition();
		Player->Attack(dir); 
	}
	turns++;
}
bool GameManager::GetPlayerTurn() const
{
	return isPlayerTurn;
}
Entity* GameManager::GetPlayer() const
{
	return Player;
}
bool GameManager::GetGameEnded() const
{
	return GameEnded;
}
bool GameManager::GetGameWon() const
{
	return GameWon;
}
void GameManager::SetPlayer(Entity* toEntity) 
{
	Player = toEntity;
}
bool GameManager::isAllGoblinsDead() const
{
	return goblinCount <=0;
}
void GameManager::RemoveGoblin(Goblin* gob)
{
	Goblins = ArrayRemove(Goblins, gob, goblinCount, true);
}

GameManager* GameManager::getGM()
{
	return GM_Instance;
}

void GameManager::Exit()
{
	if(Goblins)
	delete[] Goblins;
}

void GameManager::PromptInput()
{
	isPlayerTurn = true;
	Scene::GotoXY(0, 12);
	cout << "Player Option Move (W)(A)(S)(D) Attack(I)(J)(K)(L) \n Input:                                                        ";
	Scene::GotoXY(7, 13);
}
