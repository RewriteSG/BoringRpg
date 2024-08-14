#pragma once
#include <iostream>
#include "Vector2.h"
class OptionUI
{
private:
	Vector2 position;
	std::string** options;
	int optionsSize;
	int optionsCapacity;
	int textColor;

private:
	void reallocOption(const int newCapacity);
	void PrintOption(const std::string option, const int color) const;

public:
	OptionUI(Vector2 position, const int& color);
	~OptionUI(void);
	int PeekIndex(const std::string item) const;
	void AddOption(std::string* text);
	void RemoveOption(std::string* text);
	void RemoveOption(const int itemIndex);
	void Clear(void) const;
	int PickOption(const Vector2 position) const;
};

