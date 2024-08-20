#include "TimeSystem.h"
#include "string"
#include "GameManager.h"
#include "InventoryManager.h"
#include "InteractionsManager.h"
TimeSystem::TimeSystem()
{
	TimeLoop = 3;
	TimeTaken = 0;
	// 720 = 12 minutes
	RobberTime = 120;
	TimeLimitForCops = 300;
}

void TimeSystem::CountLoop(int time)
{
	TimeLoop++;
	TimeTaken = 0;
	GameManager::getGM()->LoopStarted = false;
	GameManager::getGM()->inventory = InventoryManager();
	GameManager::getGM()->InteractionsMgr = InteractionsManager();

}

void TimeSystem::increaseTimeTaken(int time)
{
	TimeTaken += time;
}

void TimeSystem::decreaseTimeTaken(int time)
{
	TimeTaken -= time;
}
void TimeSystem::increaseRobberTime(int time) {
	RobberTime += time;
}

std::string TimeSystem::GetTimeinString(int time)
{

	//display time in min & sec
	int minute = time / 60;
	int second = time % 60;
	std::string toReturn;
	toReturn += "TIME: 00:";
	std::string minuteStr = ((minute < 10) ? "0" + std::to_string(minute) : std::to_string(minute)) + ":";
	std::string secondStr = (second < 10) ? "0" + std::to_string(second) : std::to_string(second);

	toReturn += minuteStr + secondStr; 
	//std::cout << minute << ":" << second << std::endl;
	return toReturn;
}
//if TimeLimit <=0{
// TimeLoop++;
//  >return TimeLimit = 12;
//}