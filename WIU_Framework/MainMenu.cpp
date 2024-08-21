#include "MainMenu.h"
#include "SceneManager.h"
#include "ExampleScene.h"
#include "BedroomScene.h"
#include "LivingRoomScene.h"
#include "ToiletScene.h"
#include "StoreRoomScene.h"
#include "Application.h"
#include "Endings.h"
#include "SpatialInteractionManagerInterop.h"
#include "Endings.h"
#include "UI.h"
#include "KitchenScene.h"
#include "conio.h" 

void MainMenu::DrawClock(const int size) const
{
	const int width = size * 2;
	const int positionX = Application::numberOfColumns / 2 - width / 2;
	const int positionY = Application::numberOfRows / 2 - size / 2;

	for (int i = 0; i < size; ++i)
	{
		Scene::GotoXY(0, i, Vector2(positionX, positionY));
		for (int j = 0; j < width; ++j)
		{
			if (i == 0 || i == size - 1)
			{
				Scene::ChangeColor(Scene::BG_COLOR);
				std::cout << " ";
			}
			else
			{
				if (j == 0 || j == 1 || j == width - 2 || j == width - 1)
				{
					Scene::ChangeColor(Scene::BG_COLOR);
					std::cout << " ";
				}
				else
				{
					Scene::ChangeColor(Scene::White);
					std::cout << " ";
				}
			}
		}
	}

	Scene::ChangeColor(112);
	Scene::GotoXY(width / 2, size / 2 - 13, Vector2(positionX, positionY));
	std::cout << "12";
	Scene::GotoXY(width / 2, size / 2 + 12, Vector2(positionX, positionY));
	std::cout << "6";
	Scene::GotoXY(width / 2 + 25, size / 2 - 1, Vector2(positionX, positionY));
	std::cout << '3';
	Scene::GotoXY(width / 2 - 26, size / 2 - 1, Vector2(positionX, positionY));
	std::cout << '9';

	for (int i = 0; i < 12; ++i)
	{
		Scene::ChangeColor(0);

		if (i < 10)
		{
			Scene::GotoXY(width / 2, size / 2 - i, Vector2(positionX, positionY));
			std::cout << " ";
		}



		Scene::GotoXY(width / 2 - i, size / 2 - i, Vector2(positionX, positionY));
		std::cout << " ";
	}
}

void MainMenu::Start(void)
{
	Scene::ChangeColor(112);
	std::string title = " EVERY SECOND COUNTS ";
	Scene::GotoXY(Application::numberOfColumns / 2 - (int)title.length() / 2, 4);
	std::cout << title;

	DrawClock(30);
}

void MainMenu::Update(void)
{
	std::string choices[3] = { "Start New Game", "Endings", "Exit" };

	if (GameManager::getGM()->TimeSys.TimeLoop > 0)
		choices[0] = "Continue";

	int counter = 1;
	char key;
	int set[] = { 112, 112, 112 };
	while (true)
	{
		set[0] = 112;
		set[1] = 112;
		set[2] = 112;
		if (counter == 1)
			set[0] = 116;
		if (counter == 2)
			set[1] = 116;
		if (counter == 3)
			set[2] = 116;

		for (int i = 0; i < 3; ++i)
		{
			Scene::GotoXY(Application::numberOfColumns / 2 - (int)choices[i].length() / 2, Application::numberOfRows / 2 + i + 2);
			Scene::ChangeColor(set[i]);
			std::cout << choices[i];
		}

		key = _getch();

		if (key == 'w' && (counter > 1 && counter <= 3))
			counter--;

		if (key == 's' && (counter > 0 && counter <= 2))
			counter++;

		if (key == '\r')
		{
			if (counter == 1) {
				Scene::ChangeColor(Scene::Default);
				system("cls");
				if (GameManager::getGM()->TimeSys.TimeLoop < 1)
				{
				UI ui = UI(Vector2(130, 12), 7, 100);
				UI gameUI2(Vector2(Application::numberOfColumns / 2 - 171 / 2, 8), 0, 171);
				//gameUI2.CreateBox(Vector2(), "", 40);
				ui.PrintDialogue(Vector2(-105, 10), "You came home late from work, tired and exhausted.");
				ui.PrintDialogue(Vector2(-105, 10), "You: There's so much work lately, and it's non-stop...");
				ui.PrintDialogue(Vector2(-105, 10), "You: When will this boring life ever end?");
				ui.PrintDialogue(Vector2(-105, 10), "You thought to yourself, and continued your journey back home.");
				ui.PrintDialogue(Vector2(-105, 10), "As you reached your doorstep, you heard someone behind you.");
				ui.PrintDialogue(Vector2(-105, 10), "You turned around, only to see a black figure dissapearing into the alley.");
				ui.PrintDialogue(Vector2(-105, 10), "You: Is anyone there?");
				ui.PrintDialogue(Vector2(-105, 10), "But there was only silence.");
				ui.PrintDialogue(Vector2(-105, 10), "You: Maybe I'm just... hallucinating?");
				ui.PrintDialogue(Vector2(-105, 10), "You reached into your pockets for your key, and unlocked the door.");
				ui.PrintDialogue(Vector2(-105, 10), "Just as you close your door, the figure appears from the dark.");
				ui.PrintDialogue(Vector2(-105, 10), "With a knife in his hand.");

				}
				SceneManager::LoadScene(new LivingRoomScene());
			}
				
			else if (counter == 2)
			{
				Scene::ChangeColor(Scene::Default);
				system("cls");
				UI ui = UI(Vector2(130, 12), 0, 200);
				UI gameUI2(Vector2(Application::numberOfColumns / 2 - 171 / 2, 8), 0, 171);
				ui.PrintDialogue(Vector2(-105, 10), "Heres the place where will show all the unlocked endings. Press 'Enter'for the next ending");
				SceneManager::LoadScene(SceneManager::endingsPage);
			}
			else
				SceneManager::isExit = true;

			break;
		}
	}
}

void MainMenu::Render(void)
{
}

void MainMenu::Exit(void)
{
	Scene::ChangeColor(Scene::Default);
}


