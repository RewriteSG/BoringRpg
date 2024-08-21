#include "OptionUI.h"
#include "Scene.h"
#include "Application.h"
#include "string"

OptionUI::OptionUI(Vector2 _position, const int& color, const bool _isCenter) : position(_position), optionsSize(0), optionsCapacity(0), isCenter(_isCenter)
{
	textColor = color;
	reallocOption(2);
}
OptionUI::~OptionUI(void)
{
	if(optionsSize > 0)
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
	Scene::ChangeColor(Scene::Yellow,true);
	std::cout << option;
	Scene::ChangeColor(Scene::Default, true);
}

void OptionUI::AddOption(std::string* text)
{
	if (optionsSize >= optionsCapacity)
		reallocOption(optionsCapacity + optionsCapacity / 2);

	options[optionsSize++] = text;
}

int OptionUI::size() const {return optionsSize;}

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

void OptionUI::Clear(void)
{
	for (int i = 0; i < optionsSize; ++i)
		delete options[i];

	optionsSize = 0;
}

int OptionUI::PickOption(const Vector2 position) const
{
	int choosenOption = 0;
	Scene::ChangeColor(Scene::Yellow, true);
	for (int i = 0; i < optionsSize; ++i)
	{
		Scene::GotoXY(position.GetX(), position.GetY() + i, this->position);
		//Scene::ChangeColor(textColor);
		std::cout << *options[i];
	}
	Scene::ChangeColor(Scene::Default, true);

	std::string input{};

	bool isCheckDone = false;
	while (!isCheckDone)
	{
		input = GameManager::InputField();

		for (int i = 0; i < optionsSize; ++i)
		{
			if (input == Scene::tolowerString(*options[i]))
			{
				isCheckDone = true;
				choosenOption = i;
				break;
			}
		}
	}

	for (int i = 0; i < optionsSize + 1; ++i)
	{
		Scene::GotoXY(position.GetX(), position.GetY() + i, this->position);
		for (int i = 0; i < 100; ++i)
			std::cout << " ";
	}
	return choosenOption;
}