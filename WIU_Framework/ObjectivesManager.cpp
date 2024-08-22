#include "ObjectivesManager.h"
#include "InteractionsManager.h"
#include "GameManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "Furniture.h"
#include "Windows.h"
#define objectiveY -5
ObjectivesManager::ObjectivesManager()
{
	hasCalledMom = false;
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
				//if (!hasCalledMom)
			if (!hasTakenShower)
			{
				ui->CreateText("              ", Vector2(29, objectiveY));
				ui->CreateText("Take a shower", Vector2(29, objectiveY));
			}
			else if (!hasWatchedTV && hasTakenShower)
			{
				ui->CreateText("              ", Vector2(29, objectiveY));
				ui->CreateText("Watch TV", Vector2(29, objectiveY));
			}
			else if (!hasCalledMom && hasWatchedTV && hasTakenShower)
				{
					ui->CreateText("              ", Vector2(29, objectiveY));
					ui->CreateText("Call Mom", Vector2(29, objectiveY));
				}
			else if (!hasSlept && hasCalledMom && hasWatchedTV && hasTakenShower)
			{
				ui->CreateText("              ", Vector2(29, objectiveY));
				ui->CreateText("Go to bed", Vector2(29, objectiveY));
			}
			
			break;
		case 1:
			//	if (!hasCalledMom)
			if (!hasTakenShower)
			{
				ui->CreateText("              ", Vector2(29, objectiveY));
				ui->CreateText("Take a shower", Vector2(29, objectiveY));
			}
			else if (!hasWatchedTV && hasTakenShower)
			{
				ui->CreateText("              ", Vector2(29, objectiveY));
				ui->CreateText("Watch TV", Vector2(29, objectiveY));
			} 
			else if (!hasCalledMom && hasWatchedTV && hasTakenShower)
			{
				GameManager::getGM()->DontCountTime = false;
				ui->CreateText("              ", Vector2(29, objectiveY));
				ui->CreateText("Stay Awake.", Vector2(29, objectiveY));
				GameManager::getGM()->InteractionsMgr.TelevisionOtherChannelImage();
				Sleep(3000);
				GameManager::getGM()->TimeSys.TimeTaken = GameManager::getGM()->TimeSys.RobberTime;
			}
			break;
		default:
			bool* hasCalledTheCops = &(GameManager::getGM()->InteractionsMgr).hasCalledTheCops;
			if (!*hasCalledTheCops)
			{
				ui->CreateText("              ", Vector2(29, objectiveY));
				ui->CreateText("Find a way to escape from ", Vector2(29, objectiveY));
				ui->CreateText("the killer and escape the time loop", Vector2(18, objectiveY +1));
				if (InteractionsManager::LastTimeChecked)
					ui->CreateText("Last Time Checked: [" + TimeSystem::GetTimeinString(GameManager::getGM()->TimeSys.GetLastTimeChecked())+"]", Vector2(18, objectiveY + 2));
				else
					ui->CreateText("Last Time Checked: [Time: ??:??:??]", Vector2(18, objectiveY + 2));
			}
			else
			{
				ui->CreateText("              ", Vector2(29, objectiveY));
				ui->CreateText("                                   ", Vector2(18, objectiveY +1));
				ui->CreateText("Survive until the cops arrive", Vector2(29, objectiveY));
			}
			break;
	}
}
