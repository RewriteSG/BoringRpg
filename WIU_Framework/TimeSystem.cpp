#include "TimeSystem.h"
#include "string"
TimeSystem::TimeSystem()
{
	TimeLimitForRobber = 720;
	TimeLimitForCops = 900;
}

void TimeSystem::CountLoop(int time)
{
	TimeLoop++;
	TimeTaken = 0;
}

void TimeSystem::increaseTimeTaken(int time)
{
	TimeTaken += time;
}

void TimeSystem::decreaseTimeTaken(int time)
{
	TimeTaken -= time;
}
std::string TimeSystem::GetTimeinString(int time)
{
	//display time in min & sec
	int minute = time / 60;
	int second = time % 60;
	std::string toReturn;
	std::string minuteStr = std::to_string(minute) + "m";
	std::string secondStr = std::to_string(second) + "s";

	toReturn = minuteStr + secondStr; 
	//std::cout << minute << ":" << second << std::endl;
	return toReturn;
}
//if TimeLimit <=0{
// TimeLoop++;
//  >return TimeLimit = 12;
//}