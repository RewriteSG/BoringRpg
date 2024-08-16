#pragma once
#include "UI.h"
class EndingManager
{
private:
	int typeOfEnding;
	bool isEndingEnded;

	UI* ui;
public:

	enum TYPEOUTCOME
	{
		ENDING1,
		ENDING2,
		ENDING3,
		SleepingEnding
	};
	
	void EndingUnlocked(TYPEOUTCOME ending);
	void Start(void);
	void Update();
	void Exit();
};

