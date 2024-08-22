#pragma once
#define POINTX -106
#define POINTY 25
#include "GameObject.h"
#include "Entity.h"
#include "Items.h"
#include "ObjectManager.h"
#include <iostream>
#include "InteractionsManager.h"
#include "TimeSystem.h"
#include "Player.h"
#include "Robber.h"
#include "UI.h"
#include "InventoryManager.h"
#include "EndingManager.h"
#include "ObjectivesManager.h"
class Scene;

using namespace std;
/// <summary>
/// A GameManager class where it handles the Game win and lose condition as well as Handling player's input. 
/// </summary>
class GameManager
{
private:
	static GameManager* GM_Instance;
	bool GameEnded, GameWon;
	bool EmptyDialogue = true;
	EndingManager* endingMgr;
	bool isSurviveObjective;
public:
	bool LoopStarted;
	bool DontCountTime;
	UI* gameUI;
	Player* player;

	static GameManager* getGM();
	InteractionsManager InteractionsMgr;
	InventoryManager inventory;
	TimeSystem TimeSys;
	ObjectivesManager objManager;
	std::string whatScenePlayerIn;

	GameManager(void);
	~GameManager(void);

	void Start();
	void Update();
	void Exit();

	void HandleInput(void);
	static std::string InputField(void);

	bool GetGameEnded() const;
	bool GetGameWon() const;

	void DisplayFurnituresAroundPlayer(Vector2);
	void CreatePlayer(Vector2 toPos);
	void ClearDialogue();
	void SetDialogueEmpty(bool value);

	static char _getch(void);
	void setSurviveObjective(bool);
	bool getSurviveObjective();
};

