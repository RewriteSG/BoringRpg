#pragma once
#include <iostream>
class TimeSystem
{
public:
	int TimeTaken, RobberTime, TimeLimitForCops;
	int TimeLoop;
	TimeSystem();
	void CountLoop(int);
	virtual void increaseTimeTaken(int time);
	virtual void decreaseTimeTaken(int time);
	virtual void increaseRobberTime(int time);

	std::string GetTimeinString( int second);
};

