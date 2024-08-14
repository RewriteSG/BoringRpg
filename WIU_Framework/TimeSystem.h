#pragma once
#include <iostream>
class TimeSystem
{
public:
	int TimeTaken, RobberTime, TimeLimitForCops;
	int TimeLoop;
	TimeSystem();
	void CountLoop(int);
	void increaseTimeTaken(int);
	void decreaseTimeTaken(int);

	std::string GetTimeinString( int second);

	void increaseRobberTime(int);


};

