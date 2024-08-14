#pragma once
#include "OptionUI.h"
#include "DialogueUI.h"

class UI
{
private:
	Vector2 position;
	OptionUI* optionUI;
	DialogueUI* dialogueUI;

public:
	UI(const Vector2 position = Vector2(0, 0));
	~UI(void);

	void CreateOptionUI(const std::string label, const int color, const int width, const int height);
	OptionUI* GetOptionUI(void) const;

	void CreateDialogueUI(const std::string label, const int color, const int width, const int height);
	DialogueUI* GetDialogueUI(void) const;
};