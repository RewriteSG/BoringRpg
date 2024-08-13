#include "BedroomTableSprite.h"
#include "World.h"
#include "Scene.h"
#include <iostream>

void BedroomTableSprite::Render(int x, int y, Vector2 topLeft)
{

	/*Scene::GotoXY(x + (CellX * x), 0 + y + (y * CellY), topLeft);
	std::cout << " ";*/
	if (x >= 10) {

		cin;
	}

	Scene::GotoXY(0 + x + (CellX * x), 0 + y + (y * CellY), topLeft);
	Scene::ChangeColor(Scene::White, true);
	std::cout << "----------------";

	Scene::GotoXY(0 + x + (CellX * x), 1 + y + (y * CellY), topLeft);
	std::cout << "|";

	Scene::GotoXY(14 + x + (CellX * x), 1 + y + (y * CellY), topLeft);
	std::cout << " |";
	Scene::GotoXY(0 + x + (CellX * x), 2 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(14 + x + (CellX * x), 2 + y + (y * CellY), topLeft);
	std::cout << " |";
	Scene::GotoXY(0 + x + (CellX * x), 3 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(14 + x + (CellX * x), 3 + y + (y * CellY), topLeft);
	std::cout << " |";
	Scene::GotoXY(0 + x + (CellX * x), 4 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(14 + x + (CellX * x), 4 + y + (y * CellY), topLeft);
	std::cout << " |";
	Scene::GotoXY(2 + x + (CellX * x), 2 + y + (y * CellY), topLeft);
	std::cout << " |";
	Scene::GotoXY(5 + x + (CellX * x), 2 + y + (y * CellY), topLeft);
	std::cout << " |";
	Scene::GotoXY(4 + x + (CellX * x), 1 + y + (y * CellY), topLeft);
	std::cout << "__";
	Scene::GotoXY(4 + x + (CellX * x), 2 + y + (y * CellY), topLeft);
	std::cout << "__";
	Scene::GotoXY(4 + x + (CellX * x), 3 + y + (y * CellY), topLeft);
	std::cout << "==";
	Scene::GotoXY(7 + x + (CellX * x), 3 + y + (y * CellY), topLeft);
	std::cout << "0";
	Scene::GotoXY(8 + x + (CellX * x), 2 + y + (y * CellY), topLeft);
	std::cout << " |";
	Scene::GotoXY(11 + x + (CellX * x), 2 + y + (y * CellY), topLeft);
	std::cout << " |";
	Scene::GotoXY(8 + x + (CellX * x), 3 + y + (y * CellY), topLeft);
	std::cout << " |";
	Scene::GotoXY(11 + x + (CellX * x), 3 + y + (y * CellY), topLeft);
	std::cout << " |";
	Scene::GotoXY(10 + x + (CellX * x), 1 + y + (y * CellY), topLeft);
	std::cout << "__";
	Scene::GotoXY(10 + x + (CellX * x), 3 + y + (y * CellY), topLeft);
	std::cout << "__";
	/*Scene::GotoXY(0 + x + (CellX * x), 3 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(0 + x + (CellX * x), 3 + y + (y * CellY), topLeft);
	std::cout << "|";*/
	Scene::GotoXY(1 + x + (CellX * x), 4 + y + (y * CellY), topLeft);
	std::cout << "--------------";

	Scene::ChangeColor(Scene::Default);

}