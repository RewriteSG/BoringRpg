#pragma once
class AnxietySystem
{
	float AnxietyAmnt;
	float AnxietyLimit;
	bool hasBlockedAnxiety;
public:
	AnxietySystem();
	void SetBlockedAnxiety(bool toSet);
	void IncreaseAnxietyAmount(const int& increaseBy);
	int GetAnxietyAmount()const;
	int GetAnxietyLimit()const;
	bool isFailEvent(const float& basePercent) const;

};

