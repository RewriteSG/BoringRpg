#include "ToiletScene.h"
#include "SceneManager.h"
#include "Player.h"
#include "Wall.h"
#include "Furniture.h"
#include "UI.h"
#include "conio.h"
void ToiletScene::Start()
{
	Scene::Start();
	new Wall(Vector2(4, 2));
	new Wall(Vector2(5, 2));
	new Wall(Vector2(6, 2));
	new Wall(Vector2(8, 2));
	new Wall(Vector2(4, 3));
	new Wall(Vector2(4, 4));
	new Wall(Vector2(4, 5));
	new Wall(Vector2(4, 6));
	new Wall(Vector2(5, 6));
	new Wall(Vector2(6, 6));
	new Wall(Vector2(7, 6));
	new Wall(Vector2(8, 6));
	new Wall(Vector2(9, 2));
	new Wall(Vector2(9, 3));
	new Wall(Vector2(9, 4));
	new Wall(Vector2(9, 5));
	new Wall(Vector2(9, 6));

	new Furniture(Furniture::LivingRoomDoor, Vector2(7, 2));
	new Furniture(Furniture::ToiletBowl, Vector2(5, 3));
	new Furniture(Furniture::ShowerArea, Vector2(8, 5));
	new Furniture(Furniture::ToiletCabinet, Vector2(5, 5));
	gm.CreatePlayer(Vector2(7, 3));

	UI gameUI(Vector2(130, 12));
	gameUI.CreateBox(Vector2(), "Inventory:", 40, 15);
	gameUI.CreateBox(Vector2(0, 17), "Dialogue:", 40, 10);
}

void ToiletScene::Update()
{
	Scene::Update();
}
