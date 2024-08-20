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
#include "UI.h"
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
	std::string tittle = " EVERY SECOND COUNTS ";
	Scene::GotoXY(Application::numberOfColumns / 2 - (int)tittle.length() / 2, 4);
	std::cout << tittle;

	DrawClock(30);
}

void MainMenu::Update(void)
{
	std::string choices[3] = { "Play", "Endings", "Exit" };
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

		key = GameManager::_getch();

		if (key == 'w' && (counter > 1 && counter <= 3))
			counter--;

		if (key == 's' && (counter > 0 && counter <= 2))
			counter++;

		if (key == '\r')
		{
			if (counter == 1) {
				Scene::ChangeColor(Scene::Default);
				system("cls");
				UI ui = UI(Vector2(130, 12), 7);
				UI gameUI2(Vector2(Application::numberOfColumns / 2 - 171 / 2, 8), 0, 171);
				//gameUI2.CreateBox(Vector2(), "", 40);
				ui.PrintDialogue(Vector2(-105, 10), "You came home from work, tired and exhausted.");
				ui.PrintDialogue(Vector2(-105, 10), "You: Damn... so many customers today...");
				ui.PrintDialogue(Vector2(-105, 10), "You: I really need to get some rest...");
				ui.PrintDialogue(Vector2(-105, 10), "As you arrived at the door, you reached for your keys in your pocket.");
				ui.PrintDialogue(Vector2(-105, 10), "When you insert the key and turned, you walked into the living room.");
				ui.PrintDialogue(Vector2(-105, 10), "You decide to watch the news first before going to bed.");

				SceneManager::LoadScene(new LivingRoomScene());

			}
				
			else if (counter == 2)
			{
				Scene::ChangeColor(Scene::Default);
				system("cls");
				UI ui = UI(Vector2(130, 12), 7);
				UI gameUI2(Vector2(Application::numberOfColumns / 2 - 171 / 2, 8), 0, 171);
				ui.PrintDialogue(Vector2(-105, 10), "Heres the place where will show all the unlocked endings. Press 'Enter'for the next ending");
				SceneManager::LoadScene(new Endings());
			}
			else
				exit(0);

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


