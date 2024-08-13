#include "DialogueUI.h"
#include "Windows.h"
#include "Scene.h"
#include "conio.h"

DialogueUI::DialogueUI(const Vector2 _position, const int _color) : position(_position), text(nullptr), color(_color)
{
}

void DialogueUI::PrintDialogue(const Vector2 position, const GameObject* go, const std::string text)
{
	Scene::ChangeColor(color);
	Scene::GotoXY(position.GetX(), position.GetY(), this->position);
	std::string textToPrint = go->GetName() + ": " + text;

	char input{};
	for (char& ch : textToPrint)
	{
		if (_kbhit())
		{
			input = GameManager::_getch();

			if (input == '\r')
			{
				Scene::GotoXY(position.GetX(), position.GetY(), this->position);
				std::cout << textToPrint;
				break;
			}
		}

		std::cout << ch;
		Sleep(70);
	}

	while (true)
	{
		input = GameManager::_getch();
		if (input == '\r')
			break;
	}

	Scene::ChangeColor(Scene::BG_COLOR);
	Scene::GotoXY(position.GetX(), position.GetY(), this->position);
	for (char& ch : textToPrint)
		std::cout << ' ';
}
