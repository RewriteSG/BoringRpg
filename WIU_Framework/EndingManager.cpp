#include "EndingManager.h"
#include "Application.h"
#include "GameManager.h"

void EndingManager::PlayLivingRoom(void)
{
	dialogues.push_back("Killer broke into living room");

	if (GameManager::getGM()->InteractionsMgr.isNailSetup)
		dialogues.push_back("The serial killer has stepped on the nails. This will take some time for the serial killer to recover.");
	
	if (isPlayerWithKiller)
		isPlayerGetKilled = true;
}

void EndingManager::Update()
{
	ui = new UI(Vector2(Application::numberOfColumns / 2, Application::numberOfRows / 2));

	for (int i = 0; i < 5; ++i)
	{
		killerCurrentScene = SceneManager::GetSceneName(i);
		isPlayerWithKiller = GameManager::getGM()->whatScenePlayerIn == killerCurrentScene;

		switch (i)
		{
		case 0:
			PlayLivingRoom();
			break;
		case 1:
			//
			break;
		case 2:
			//
			break;
		case 3:
			//
			break;
		case 4:
			//
			break;
		}

		if()
	}
}
