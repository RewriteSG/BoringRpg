#pragma once
#include <iostream>
class TimeSystem
{
public:
	int TimeTaken, RobberTime, TimeLimitForCops;
	int TimeLoop;
	TimeSystem();
	void CountLoop(int);
	void increaseTimeTaken(int time);
	void decreaseTimeTaken(int time);
	void increaseRobberTime(int time);

	std::string GetTimeinString( int second);



};

