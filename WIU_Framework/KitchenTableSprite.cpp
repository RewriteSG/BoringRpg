#include "KitchenTableSprite.h"
#include "World.h"
#include "Scene.h"
#include <iostream>

void KitchenTableSprite::Render(int x, int y, Vector2 topLeft)
{

	/*Scene::GotoXY(x + (CellX * x), 0 + y + (y * CellY), topLeft);
	std::cout << " ";*/
	if (x >= 10) {

		cin;
	}

	Scene::GotoXY(2 + x + (CellX * x), 0 + y + (y * CellY), topLeft);
	Scene::ChangeColor(Scene::White, true);
	std::cout << "--------------------------------------";
	Scene::GotoXY(1 + x + (CellX * x), 1 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(1 + x + (CellX * x), 2 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(2 + x + (CellX * x), 3 + y + (y * CellY), topLeft);
	std::cout << "--------------------------------";
	Scene::GotoXY(33 + x + (CellX * x), 4 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(33 + x + (CellX * x), 5 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(33 + x + (CellX * x), 6 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(33 + x + (CellX * x), 7 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(33 + x + (CellX * x), 8 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(33 + x + (CellX * x), 9 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(33 + x + (CellX * x), 10 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(33 + x + (CellX * x), 11 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(33 + x + (CellX * x), 12 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(33 + x + (CellX * x), 13 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(33 + x + (CellX * x), 14 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(39 + x + (CellX * x), 1 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(39 + x + (CellX * x), 2 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(39 + x + (CellX * x), 3 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(39 + x + (CellX * x), 4 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(39 + x + (CellX * x), 5 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(39 + x + (CellX * x), 6 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(39 + x + (CellX * x), 7 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(39 + x + (CellX * x), 8 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(39 + x + (CellX * x), 9 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(39 + x + (CellX * x), 10 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(39 + x + (CellX * x), 11 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(39 + x + (CellX * x), 12 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(39 + x + (CellX * x), 13 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(39 + x + (CellX * x), 14 + y + (y * CellY), topLeft);
	std::cout << "|";
	Scene::GotoXY(34 + x + (CellX * x), 15 + y + (y * CellY), topLeft);
	std::cout << "-----";
	
	

}