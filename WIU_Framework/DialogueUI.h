#pragma once
#include <iostream>
#include "ObjectManager.h"
class DialogueUI
{
private:
	Vector2 position;
	std::string* text;
	int color;
public:
	DialogueUI(const Vector2 _position, const int _color);
	void PrintDialogue(const Vector2 position = Vector2(0, 0), const GameObject* go = nullptr, const std::string text = " ");
};

