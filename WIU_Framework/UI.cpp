#include "UI.h"
#include "Scene.h"

UI::UI(const Vector2 _position) : dialogueUI(nullptr), optionUI(nullptr), position(_position)
{
	Scene::GotoXY(position.GetX(), position.GetY());
}

UI::~UI(void)
{
	if (optionUI != nullptr)
	{
		optionUI->Clear();
		delete optionUI;
	}
}

void UI::CreateOptionUI(const int color)
{
	optionUI = new OptionUI(position, color);
}

void UI::CreateDialogueUI(const int color)
{
	dialogueUI = new DialogueUI(position, color);
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
