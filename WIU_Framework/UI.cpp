#include "UI.h"
#include "Scene.h"
#include "conio.h"
#include "Windows.h"

UI::UI(const Vector2 _position, const int _color) : optionUI(nullptr), position(_position), color(_color)
{
	Scene::ChangeColor(_color);
}

UI::~UI(void)
{
	if (optionUI != nullptr)
		delete optionUI;
}

void UI::CreateBorder(const Vector2 position,  int width, const int height) const
{
	Scene::ChangeColor(color);
	for (int i = 0; i < height; ++i)
	{
		Scene::GotoXY(position.GetX(), position.GetY() + i, this->position);
		for (int j = 0; j < width; ++j)
		{
			std::cout << " ";
		}
	}
}

void UI::CreateBox(const Vector2 position, const std::string text, const int width, const int height) const
{
	Scene::GotoXY(position.GetX(), position.GetY(), this->position);
	CreateBorder(position, width, height);
	CreateText(text, position);
}
void UI::CreateText(const std::string text, const Vector2 position) const
{
	Scene::GotoXY(position.GetX(), position.GetY(), this->position);
	Scene::ChangeColor(color + 7);
	std::cout << text << std::endl;
}

void UI::CreateOptionUI(const Vector2 optionPosition, const bool isCenter)
{
	optionUI = new OptionUI(position + optionPosition, color, isCenter);
}

OptionUI* UI::GetOptionUI(void) const { return optionUI; }

void UI::PrintDialogue(const Vector2 position, const std::string text) const
{
	Scene::ChangeColor(color + 7);
	Scene::GotoXY(position.GetX(), position.GetY(), this->position);
	std::string textToPrint = text;

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

	Scene::ChangeColor(color);
	Scene::GotoXY(position.GetX(), position.GetY(), this->position);
	for (char& ch : textToPrint)
		std::cout << ' ';
}

int UI::PickDialogue(const Vector2 position, const std::string text) const
{
	int choosenOption = 0;

	Scene::ChangeColor(color);
	Scene::GotoXY(position.GetX(), position.GetY(), this->position);
	std::string textToPrint = text;

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

	if (optionUI == nullptr)
		throw std::invalid_argument("No option UI instance object");

	choosenOption =  optionUI->PickOption(Vector2(0, 2));

	Scene::ChangeColor(color);
	Scene::GotoXY(position.GetX(), position.GetY(), this->position);
	for (char& ch : textToPrint)
		std::cout << ' ';

	delete optionUI;
	return choosenOption;
}
