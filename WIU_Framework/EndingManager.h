#pragma once
#include "UI.h"
#include "Vector"
class EndingManager
{
private:
	UI* ui;
	std::string killerCurrentScene;
	bool isPlayerWithKiller;
	bool isPlayerGetKilled;
	std::vector<std::string> dialogues;
private:
	void PlayLivingRoom(void);
public:
	void Update();
	void Exit();
};
