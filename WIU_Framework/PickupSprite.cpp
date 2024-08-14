#include "PickupSprite.h"
#include "World.h"
#include "Scene.h"
#include <iostream>
void PickupSprite::Render(int x, int y, Vector2 topLeft)
{
	Scene::ChangeColor(Scene::Black);

	//Scene::GotoXY(x + (CellX * x), 0 + y + (y * CellY), topLeft);
	//std::cout << " ";


	Scene::GotoXY(3 + x + (CellX * x), 0 + y + (y * CellY), topLeft);
	Scene::ChangeColor(Scene::Yellow);
	std::cout << "K";
	Scene::ChangeColor(Scene::Default);
}