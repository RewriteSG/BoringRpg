#include "UI.h"
#include "Scene.h"

UI::UI(const Vector2 _position) : optionUI(nullptr), position(_position)
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

OptionUI* UI::GetOptionUI(void) const { return optionUI; }
