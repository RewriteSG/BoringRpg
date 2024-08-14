#pragma once
#include "GameObject.h"
#include "Entity.h"
#include "Items.h"
#include "ObjectManager.h"
#include <iostream>
#include "UI.h"
using namespace std;

/// <summary>
/// A GameManager class where it handles the Game win and lose condition as well as Handling player's input. 
/// </summary>
class GameManager
{
private:
	static GameManager* GM_Instance;
	bool GameEnded, GameWon;
	UI* gameUI;

public:
	static GameManager* getGM();
	GameManager();

	void Start();
	void Update();
	void Exit();

	void PromptInput();
	void HandleInput(void);

	bool GetGameEnded() const;
	bool GetGameWon() const;

	static char _getch(void);
};

