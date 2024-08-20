#include "ObjectivesManager.h"
#include "InteractionsManager.h"
#include "GameManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "Furniture.h"
#include "Windows.h"
ObjectivesManager::ObjectivesManager()
{

	hasTakenShower = false;
	hasWatchedTV = false;
	hasSlept = false;
}

void ObjectivesManager::displayObjectives() const
{

	UI* ui = GameManager::getGM()->gameUI;
	switch (GameManager::getGM()->TimeSys.TimeLoop)
	{
		case 0:
			if (!hasTakenShower)
			{
				ui->CreateText("              ", Vector2(29, -5));
				ui->CreateText("Take a shower", Vector2(29, -5));
			}
			else if (!hasWatchedTV && hasTakenShower)
			{
				ui->CreateText("              ", Vector2(29, -5));
				ui->CreateText("Watch TV", Vector2(29, -5));
			}
			else if (!hasSlept && hasWatchedTV && hasTakenShower)
			{
				ui->CreateText("              ", Vector2(29, -5));
				ui->CreateText("Go to bed", Vector2(29, -5));
			}
			
			break;
		case 1:
			if (!hasTakenShower)
			{
				ui->CreateText("              ", Vector2(29, -5));
				ui->CreateText("Take a shower", Vector2(29, -5));
			}
			else if (!hasWatchedTV && hasTakenShower)
			{
				ui->CreateText("              ", Vector2(29, -5));
				ui->CreateText("Watch TV", Vector2(29, -5));
			} 
			else if (hasWatchedTV && hasTakenShower)
			{
				ui->CreateText("              ", Vector2(29, -5));
				ui->CreateText("Stay Awake.", Vector2(29, -5));
				Sleep(3000);
				GameManager::getGM()->TimeSys.TimeTaken = GameManager::getGM()->TimeSys.RobberTime;
			}
			break;
		default:
			bool* hasCalledTheCops = &(GameManager::getGM()->InteractionsMgr).hasCalledTheCops;
			if (!*hasCalledTheCops)
			{
				ui->CreateText("              ", Vector2(29, -5));
				ui->CreateText("Survive", Vector2(29, -5));
			}
			else
			{
				ui->CreateText("              ", Vector2(29, -5));
				ui->CreateText("Survive until the cops arrive", Vector2(29, -5));
				ui->CreateText("(12:15)", Vector2(29, -4));
			}
			break;
	}
}
