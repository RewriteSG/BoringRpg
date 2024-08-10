#pragma once
#include "GameObject.h"
#include "Entity.h"
#include "Items.h"
#include "ObjectManager.h"
#include <iostream>
using namespace std;
/// <summary>
/// A GameManager class where it handles the Game win and lose condition as well as Handling player's input. 
/// </summary>
class GameManager
{
	static GameManager* GM_Instance;
	bool GameEnded, GameWon;

public:
	static GameManager* getGM();
	GameManager();

	void Start();
	void Update();
	void Exit();

	void PromptInput();
	void HandleInput(char input);

	bool GetGameEnded() const;
	bool GetGameWon() const;
};

