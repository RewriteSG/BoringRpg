#pragma once
#include "UI.h"
#include "Vector"
class EndingManager
{
private:
	UI* ui;
	std::string killerCurrentScene;
	bool isPlayerWithKiller;
	bool isKillerGetKill;
	bool isPlayerFound;
	bool isDuctTapeUse;
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

	void SoapAction(void);
	void ContinueDialogue(void);

public:
	EndingManager(void);
	~EndingManager();
	void Start(void);
	void Update(void);
	void Exit(void);
};