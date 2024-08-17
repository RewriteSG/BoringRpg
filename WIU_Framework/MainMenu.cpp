#include "MainMenu.h"
#include "SceneManager.h"
#include "ExampleScene.h"
#include "BedroomScene.h"
#include "LivingRoomScene.h"
#include "ToiletScene.h"
#include "StoreRoomScene.h"
#include "Application.h"
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
	UI systemUI(Vector2(Application::numberOfColumns / 2, Application::numberOfRows / 2), 112);
	systemUI.CreateOptionUI(Vector2(), true);	


	systemUI.GetOptionUI()->AddOption(new std::string("Play"));
	systemUI.GetOptionUI()->AddOption(new std::string("Endings"));
	systemUI.GetOptionUI()->AddOption(new std::string("Quit"));

	int choice = systemUI.GetOptionUI()->PickOption(Vector2(0, 5));
	Scene::ChangeColor(Scene::Default);
	switch (choice)
	{
	case 0:
		system("cls");
		SceneManager::LoadScene(new StoreRoomScene());
		break;
	case 2:
		exit(0);
		break;
	}
}

void MainMenu::Render(void)
{
}

void MainMenu::Exit(void)
{
	Scene::ChangeColor(Scene::Default);
}


