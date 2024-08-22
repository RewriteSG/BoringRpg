#include "TimeSystem.h"
#include "string"
#include "GameManager.h"
#include "InventoryManager.h"
#include "InteractionsManager.h"
TimeSystem::TimeSystem()
{
	lastTimeChecked = 0;
	TimeLoop = 3;
	TimeTaken = 0;
	RobberTime = 300;
	TimeLimitForCops = 480;
	increasedTime = false;
	lastTimeChecked = 0;
}

void TimeSystem::CountLoop(void)
{	TimeLoop++;
	TimeTaken = 0;
	lastTimeChecked = 0;
	GameManager::getGM()->LoopStarted = false;
	GameManager::getGM()->inventory = InventoryManager();
	GameManager::getGM()->InteractionsMgr = InteractionsManager();
	increasedTime = false;
}

void TimeSystem::increaseTimeTaken(int time)
{
	TimeTaken += time;
	increasedTime = true;
	if (increasedTime)
		InteractionsManager::LastTimeChecked = false;
}
void TimeSystem::increaseTimeTaken(int time, bool)
{
	TimeTaken += time;
	if (increasedTime)
		InteractionsManager::LastTimeChecked = false;
}
void TimeSystem::checkedTime(int time)
{
	InteractionsManager::LastTimeChecked = true;
	lastTimeChecked = TimeTaken;
	increasedTime = false;
}
void TimeSystem::increaseRobberTime(int time) {
	RobberTime += time;
}

int TimeSystem::GetLastTimeChecked() const
{
	return lastTimeChecked;
}

std::string TimeSystem::GetTimeinString(int time)
{
	int minute = time / 60;
	int second = time % 60;
	std::string toReturn;
	toReturn += "TIME: 00:";
	std::string minuteStr = ((minute < 10) ? "0" + std::to_string(minute) : std::to_string(minute)) + ":";
	std::string secondStr = (second < 10) ? "0" + std::to_string(second) : std::to_string(second);

	toReturn += minuteStr + secondStr; 
	return toReturn;
}