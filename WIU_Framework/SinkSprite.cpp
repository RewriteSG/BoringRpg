#include "SinkSprite.h"
#include "World.h"
#include "Scene.h"
#include <iostream>

void SinkSprite::Render(int x, int y, Vector2 topLeft)
{

	/*Scene::GotoXY(x + (CellX * x), 0 + y + (y * CellY), topLeft);
	std::cout << " ";*/
	if (x >= 10) {

		cin;
	}

	Scene::GotoXY(0 + x + (CellX * x), 0 + y + (y * CellY), topLeft);
	Scene::ChangeColor(Scene::White, true);
	std::cout << "	 _______";
	Scene::GotoXY(0 + x + (CellX * x), 1 + y + (y * CellY), topLeft);
	std::cout << " ______|       |";
	Scene::GotoXY(0 + x + (CellX * x), 2 + y + (y * CellY), topLeft);
	std::cout << "|	|  ---  |";
	Scene::GotoXY(0 + x + (CellX * x), 3 + y + (y * CellY), topLeft);
	std::cout << "|| | | | |   | |";
	Scene::GotoXY(0 + x + (CellX * x), 4 + y + (y * CellY), topLeft);
	std::cout << "|______|  ---  |";
	Scene::GotoXY(0 + x + (CellX * x), 5 + y + (y * CellY), topLeft);
	std::cout << "	|_______|";

}