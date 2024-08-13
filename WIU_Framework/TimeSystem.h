#pragma once
#include <iostream>
class TimeSystem
{
public:
	int TimeTaken, TimeLimitForRobber, TimeLimitForCops;
	int TimeLoop;
	TimeSystem();
	void CountLoop(int);
	void increaseTimeTaken(int);
	void decreaseTimeTaken(int);

	std::string GetTimeinString( int second);
};

