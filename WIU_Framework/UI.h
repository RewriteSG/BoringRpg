#pragma once
#include "OptionUI.h"

class UI
{
private:
	Vector2 position;
	OptionUI* optionUI;

public:
	UI(const Vector2 position = Vector2(0, 0));
	~UI(void);

	void CreateOptionUI(const int color);
	OptionUI* GetOptionUI(void) const;
};