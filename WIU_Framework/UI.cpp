#include "UI.h"
#include "Scene.h"
#include "conio.h"
#include "Windows.h"


int UI::rows = 0;

UI::UI(const Vector2 _position, const int _color) : optionUI(nullptr), position(_position), color(_color)
{
	Scene::ChangeColor(_color);
}

UI::UI(const Vector2 _position, const int _color, const int rows) : optionUI(nullptr), position(_position), color(_color)
{
	this->rows = rows;
}

UI::~UI(void)
{
	if (optionUI != nullptr)
		delete optionUI;
}

void UI::CreateBorder(const Vector2 position,  const int height) const
{
	Scene::ChangeColor(color);
	for (int i = 0; i < height; ++i)
	{
		Scene::GotoXY(position.GetX(), position.GetY() + i, this->position);
		for (int j = 0; j < rows; ++j)
		{
			if (i == 0 || i == height - 1)
			{
				Scene::ChangeColor(Scene::White);
				std::cout << " ";
			}
			else
			{
				if (j == 0 || j == 1 || j == rows - 2 || j == rows - 1)
				{
					Scene::ChangeColor(Scene::White);
					std::cout << " ";
				}
				else
				{
					Scene::ChangeColor(Scene::Black);
					std::cout << " ";
				}
			}
		}
	}
}

void UI::CreateBox(const Vector2 position, const std::string text, const int height) const
{
	Scene::GotoXY(position.GetX(), position.GetY(), this->position);
	CreateBorder(position, height);
	CreateText(text, position + Vector2(3, 2));
}
void UI::CreateText(const std::string text, const Vector2 position, int color) const
{
	Scene::GotoXY(position.GetX(), position.GetY(), this->position);
	Scene::ChangeColor((color + 7 != this->color) ? color + 7 : this->color);
	std::cout << text << std::endl;
}

void UI::CreateOptionUI(const Vector2 optionPosition, const bool isCenter)
{
	optionUI = new OptionUI(position + optionPosition, color, isCenter);
}

OptionUI* UI::GetOptionUI(void) const { return optionUI; }

void UI::PrintDialogue(Vector2 position, const std::string text) const
{
	Vector2 originalPos = position;
	Scene::ChangeColor(color + 7);
	Scene::GotoXY(position.GetX(), position.GetY(), this->position);
	std::string textToPrint = text + ' ';

	int numCh = 0;
	char input = ' ';
	int duration = 70;
	int numOfCharsInLine = 0;
	int numberOfLine = 1;
	for (char& ch : textToPrint)
	{
		if (_kbhit())
		{
			input = GameManager::_getch();

			if (input == '\r')
			{
				duration = 0;
			}
		}

		if (ch == ' ') {
			if (numCh - numOfCharsInLine >= rows - 6)
			{
				position.GetY()++; 
				Scene::GotoXY(position.GetX(), position.GetY(), this->position);
				numOfCharsInLine += numCh;
				numberOfLine++;
				numCh = 0; 
			}
		}
		else {
			for (int i = numCh + numOfCharsInLine; i < textToPrint.length(); i++)
			{
				char whatisThat = textToPrint[i];
				if (textToPrint[i] == ' ') 
				{
					if (i - 1 - numOfCharsInLine >= rows - 6) 
					{
						position.GetY()++;
						Scene::GotoXY(position.GetX() , position.GetY(), this->position);
						numOfCharsInLine += numCh;
						numberOfLine++;
						numCh = 0;
					}
					break;
				}

			}
		}
		if (!(ch == ' ' && numCh == 0))
			std::cout << ch;

		numCh++;
		Sleep(duration);
	}

	while (true)
	{
		input = GameManager::_getch();
		if (input == '\r')
			break;
	}

	numCh = 0;
	Scene::ChangeColor(color);
	for (int i = 0; i < numberOfLine; ++i)
	{
		Scene::GotoXY(position.GetX(), originalPos.GetY() + i, this->position);
		for (int j = 0; j < 40; ++j)
		{
			std::cout << ' ';
		}
	}
}

int UI::PickDialogue(Vector2 position, const std::string text) const
{
	Vector2 originalPos = position;
	int choosenOption = 0;

	Scene::ChangeColor(color);
	Scene::GotoXY(position.GetX(), position.GetY(), this->position);
	std::string textToPrint = text + ' ';

	int numCh = 0;
	char input = ' ';
	int duration = 70;
	int numOfCharsInLine = 0;
	int numberOfLine = 1;
	for (char& ch : textToPrint)
	{
		if (_kbhit())
		{
			input = GameManager::_getch();

			if (input == '\r')
			{
				duration = 0;
			}
		}

		if (ch == ' ') {
			if (numCh - numOfCharsInLine >= rows - 6)
			{
				position.GetY()++;
				Scene::GotoXY(position.GetX(), position.GetY(), this->position);
				numOfCharsInLine += numCh;
				numberOfLine++;
				numCh = 0;
			}
		}
		else {
			for (int i = numCh + numOfCharsInLine; i < textToPrint.length(); i++)
			{
				char whatisThat = textToPrint[i];
				if (textToPrint[i] == ' ')
				{
					if (i - 1 - numOfCharsInLine >= rows - 6)
					{
						position.GetY()++;
						Scene::GotoXY(position.GetX(), position.GetY(), this->position);
						numOfCharsInLine += numCh;
						numberOfLine++;
						numCh = 0;
					}
					break;
				}

			}
		}
		if (!(ch == ' ' && numCh == 0))
			std::cout << ch;
		Sleep(duration);
		numCh++;
	}

	if (optionUI == nullptr || optionUI->size() < 1)
		throw std::invalid_argument("No option UI instance object");
	choosenOption =  optionUI->PickOption(Vector2(0, 2));

	numCh = 0;
	Scene::ChangeColor(color);
	for (int i = 0; i < numberOfLine; ++i)
	{
		Scene::GotoXY(position.GetX(), originalPos.GetY() + i, this->position);
		for (int j = 0; j < 40; ++j)
		{
			std::cout << ' ';
		}
	}

	delete optionUI;
	return choosenOption;
}
