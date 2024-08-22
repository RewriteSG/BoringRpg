#pragma once
#include <iostream>
class TimeSystem
{
	bool increasedTime;
	int lastTimeChecked;
public:
	int TimeTaken, RobberTime, TimeLimitForCops;
	int TimeLoop;
	TimeSystem();
	void CountLoop(int);
	void increaseTimeTaken(int time);
	void increaseTimeTaken(int time, bool);
	void checkedTime(int time);
	void increaseRobberTime(int time);
	int GetLastTimeChecked();

	//std::string GetTimeinString( int second);

	static std::string GetTimeinString(int second);


};

