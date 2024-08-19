#include "ObjectivesManager.h"
#include "InteractionsManager.h"
#include "GameManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "Furniture.h"

void ObjectivesManager::displayObjectives()
{
	UI* ui = GameManager::getGM()->gameUI;
	switch (GameManager::getGM()->TimeSys.TimeLoop)
	{
		case 0:
			ui->PrintDialogue(Vector2(-5, -7), "Take a shower.");
			
			break;
		case 1:
			break;
		default:
			break;
	}
}
