#include "TelevisionSprite.h"
#include "World.h"
#include "Scene.h"
#include <iostream>

void TelevisionSprite::Render(int x, int y, Vector2 topLeft)
{

	/*Scene::GotoXY(x + (CellX * x), 0 + y + (y * CellY), topLeft);
	std::cout << " ";*/
	if (x >= 10) {

		cin;
	}

	Scene::GotoXY(0 + x + (CellX * x), 0 + y + (y * CellY), topLeft);
	Scene::ChangeColor(Scene::White, true);
	std::cout << "---------------";

	Scene::GotoXY(0 + x + (CellX * x), 1 + y + (y * CellY), topLeft);
	std::cout << "|";

	Scene::GotoXY(0 + x + (CellX * x), 2 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(0 + x + (CellX * x), 3 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(14 + x + (CellX * x), 1 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(14 + x + (CellX * x), 2 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(14 + x + (CellX * x), 3 + y + (y * CellY), topLeft);
	std::cout << "|";
	/*Scene::GotoXY(0 + x + (CellX * x), 3 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(0 + x + (CellX * x), 3 + y + (y * CellY), topLeft);
	std::cout << "|";*/
	Scene::GotoXY(0 + x + (CellX * x), 4 + y + (y * CellY), topLeft);
	std::cout << "---------------";
	Scene::GotoXY(6 + x + (CellX * x), 5 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(7 + x + (CellX * x), 5 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(8 + x + (CellX * x), 5 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(5 + x + (CellX * x), 5 + y + (y * CellY), topLeft);
	std::cout << "_";
	Scene::GotoXY(9 + x + (CellX * x), 5 + y + (y * CellY), topLeft);
	std::cout << "_";


	Scene::ChangeColor(Scene::Default);
}
