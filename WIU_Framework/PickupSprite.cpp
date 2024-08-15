#include "PickupSprite.h"
#include "World.h"
#include "Scene.h"
#include <iostream>
void PickupSprite::Render(int x, int y, Vector2 topLeft)
{
	Scene::ChangeColor(Scene::Black);

	//Scene::GotoXY(x + (CellX * x), 0 + y + (y * CellY), topLeft);
	//std::cout << " ";


	Scene::ChangeColor(Scene::Yellow);
	Scene::GotoXY(1 + x + (CellX * x), 5 + y + (y * CellY), topLeft);
	std::cout << "K";
	Scene::ChangeColor(Scene::Default);
}