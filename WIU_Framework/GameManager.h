#pragma once
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
	bool LoopStarted;

public:
	UI* gameUI;
	Player* player;

	static GameManager* getGM();
	InteractionsManager InteractionsMgr;
	InventoryManager inventory;
	TimeSystem TimeSys;
	EndingManager ending;
	std::string whatScenePlayerIn;
	ObjectivesManager objManager;

	GameManager();

	void Start();
	void Update();
	void Exit();

	void PromptInput();
	void HandleInput(void);
	static std::string InputField(void);

	bool GetGameEnded() const;
	bool GetGameWon() const;

	void CreatePlayer(Vector2 toPos);
	void ClearDialogue();
	static char _getch(void);
};

