#include "UI.h"
#include "Scene.h"

UI::UI(const Vector2 _position) : dialogueUI(nullptr), optionUI(nullptr), position(_position)
{
}

UI::~UI(void)
{
	if (optionUI != nullptr)
	{
		optionUI->Clear();
		delete optionUI;
	}
}

void UI::CreateOptionUI(const std::string label, const int color, const int width, const int height)
{
	optionUI = new OptionUI(position + Vector2(0, 1), color);
	for (int i = 0; i < height; ++i)
	{
		Scene::GotoXY(position.GetX(), position.GetY() + i);
		Scene::ChangeColor(color - 2);
		if (i == 0)
			std::cout << label;

		for (int j = 0; j < width; ++j)
		{
			Scene::ChangeColor(color);
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}

void UI::CreateDialogueUI(const std::string label, const int color, const int width, const int height)
{
	dialogueUI = new DialogueUI(position + Vector2(0, 1), color);
	for (int i = 0; i < height; ++i)
	{
		Scene::GotoXY(position.GetX(), position.GetY() + i);
		Scene::ChangeColor(color - 2);
		if (i == 0)
			std::cout << label;

		for (int j = 0; j < width; ++j)
		{
			Scene::ChangeColor(color);
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}

DialogueUI* UI::GetDialogueUI(void) const
{
	if (dialogueUI == nullptr)
		throw std::invalid_argument("PLEASE CREATE YOUR DIALOGUE UI :(");

	return dialogueUI;
}

OptionUI* UI::GetOptionUI(void) const { 
	if (optionUI == nullptr)
		throw std::invalid_argument("PLEASE CREATE YOUR OPTION UI :(");

	return optionUI;
}
