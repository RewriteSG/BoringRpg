#include "TimeSystem.h"
#include "string"
TimeSystem::TimeSystem()
{
	TimeLoop = 3;
	TimeTaken = 0;
	// 720 = 12 minutes
	RobberTime = 120;
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

bool TimeSystem::isTimeRunOut(void) const
{
	return TimeTaken >= RobberTime;
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