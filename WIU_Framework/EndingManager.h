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
	bool isPlayerFound;
	bool isWeaponUse;
	bool hasWeapon;
	bool isPoliceCame;
	std::vector<std::string> dialogues;
	
	bool playerGotBothWeapon;
	int dialogueIndex;
	int endingNum;
	int* time;

private:
	void PlayLivingRoom(void);
	void PlayStoreroom(void);
	void PlayToilet(void);
	void PlayBedroom(void);
	void PlayKitChen(void);

	void PickWeaponOption(void);
	void MetalPanEnding(void);
	void KnifeEnding(void);
	void MetalPanAction(void);
	void KnifeAction(void);
	void HideAction(void);

	void ContinueDialogue(void);

public:
	EndingManager(void);
	void Start(void);
	void Update(void);
	void Exit(void);
};