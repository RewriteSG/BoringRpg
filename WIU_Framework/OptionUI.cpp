#include "OptionUI.h"
#include "Scene.h"

OptionUI::OptionUI(Vector2 _position, const int& color) : position(_position), optionsSize(0), optionsCapacity(0)
{
	textColor = color;
	reallocOption(2);
}

OptionUI::~OptionUI(void)
{
	delete[] options;
}

void OptionUI::reallocOption(const int newCapacity)
{
	std::string** newBlock = new std::string * [newCapacity];

	if (newCapacity < optionsSize)
		optionsSize = newCapacity;

	for (int i = 0; i < optionsSize; ++i)
		newBlock[i] = options[i];

	delete options;
	options = newBlock;
	optionsCapacity = newCapacity;
}

void OptionUI::PrintOption(const std::string option, const int color) const
{
	Scene::ChangeColor(color);
	std::cout << option;
}

void OptionUI::AddOption(std::string* text)
{
	if (optionsSize >= optionsCapacity)
		reallocOption(optionsCapacity + optionsCapacity / 2);

	options[optionsSize++] = text;
}\

int OptionUI::PeekIndex(const std::string item) const
{
	bool isItemFound = false;
	int indexToRemove = 0;
	for (int i = 0; i < optionsSize; ++i)
	{
		if (*options[i] == item)
		{
			isItemFound = true;
			indexToRemove = i;
			break;
		}
	}

	if (!isItemFound)
		throw std::out_of_range("Item is not found");

	return indexToRemove;
}

void OptionUI::RemoveOption(std::string* text)
{
	bool isItemFound = false;
	int indexToRemove = 0;
	for (int i = 0; i < optionsSize; ++i)
	{
		if (options[i] == text)
		{
			isItemFound = true;
			indexToRemove = i;
			break;
		}
	}

	if (!isItemFound)
		throw std::out_of_range("Item is not found");

	delete options[indexToRemove];
	for (int i = indexToRemove; i < optionsSize - 1; ++i)
		options[i] = options[i + 1];
	--optionsSize;
}

void OptionUI::RemoveOption(const int itemIndex)
{
	if (itemIndex >= optionsSize)
		throw std::out_of_range("Item is not found");

	delete options[itemIndex];
	for (int i = itemIndex; i < optionsSize - 1; ++i)
		options[i] = options[i + 1];
	--optionsSize;
}

void OptionUI::Clear(void) const
{
	for (int i = 0; i < optionsSize; ++i)
		delete options[i];
}

int OptionUI::PickOption(const Vector2 position) const
{
	int counter = 1;
	int choosenOption = -1;

	int* colors = new int[optionsSize];
	for (int i = 0; i < optionsSize; ++i)
		colors[i] = textColor;

	while (true)
	{
		for (int i = 0; i < optionsSize; ++i)
		{
			if (counter - 1 == PeekIndex(*options[i]))
				colors[i] = textColor + 4;
		}

		for (int i = 0; i < optionsSize; ++i)
		{
			Scene::GotoXY(position.GetX() - (int)options[i]->length() / 2, position.GetY() + i, this->position);
			PrintOption(*options[i], colors[i]);
		}

		char key = GameManager::_getch();

		if (key == 'w' && (counter > 1 && counter <= optionsSize))
			--counter;
		else if (key == 's' && (counter > 0 && counter <= optionsSize - 1))
			++counter;

		if (key == '\r')
		{
			for (int i = 1; i <= optionsSize; ++i)
			{
				if (counter == PeekIndex(*options[i - 1]))
					choosenOption = counter;
			}
			break;
		}

		for (int i = 0; i < optionsSize; ++i)
			colors[i] = textColor;
	}

	delete[] colors;
	return choosenOption;
}