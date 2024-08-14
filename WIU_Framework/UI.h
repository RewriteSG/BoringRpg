#pragma once
#include "OptionUI.h"

class UI
{
private:
	Vector2 position;
	OptionUI* optionUI;

	int color;

	void CreateBorder(const Vector2 position, const int width, const int height) const;
public:
	UI(const Vector2 position = Vector2(0, 0), const int _color = 0);
	~UI(void);

	void CreateBox(const Vector2 position, const std::string text, const int width, const int height) const;

	void CreateText(const std::string text, const Vector2 position = Vector2()) const;

	void CreateOptionUI(const Vector2 optionPosition, const bool isCenter);
	OptionUI* GetOptionUI(void) const;

	void PrintDialogue(const Vector2 position, const std::string text) const;
	int PickDialogue(const Vector2 position, const std::string text) const;
};