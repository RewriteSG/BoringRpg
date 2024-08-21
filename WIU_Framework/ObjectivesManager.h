#pragma once
#include "string"

using namespace std;
class ObjectivesManager
{
public:
	bool hasCalledMom;
	bool hasTakenShower;
	bool hasWatchedTV;
	bool hasSlept;
	ObjectivesManager();
	void displayObjectives() const;
};

