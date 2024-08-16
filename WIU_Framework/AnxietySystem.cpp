#include "AnxietySystem.h"
#include "iostream"
AnxietySystem::AnxietySystem()
{
	hasBlockedAnxiety = false;
	AnxietyAmnt = 0;
	AnxietyLimit = 100;
}

void AnxietySystem::SetBlockedAnxiety(bool toSet)
{
	hasBlockedAnxiety = toSet;
}

void AnxietySystem::IncreaseAnxietyAmount(const int& increaseBy)
{
	AnxietyAmnt += increaseBy;
}

int AnxietySystem::GetAnxietyAmount() const
{
	return AnxietyAmnt;
}

int AnxietySystem::GetAnxietyLimit() const
{
	return AnxietyLimit;
}

bool AnxietySystem::isFailEvent(const float& basePercent) const
{
	float Percent = abs(basePercent) * (AnxietyAmnt / AnxietyLimit);
	int intergerPercent = Percent * 100;
	int random = rand() % 10000;
	return random < intergerPercent;
}
