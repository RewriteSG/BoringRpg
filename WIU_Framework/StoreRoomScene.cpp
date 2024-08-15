#include "StoreRoomScene.h"
#include "SceneManager.h"
#include "Player.h"
#include "Wall.h"
#include "Furniture.h"
#include "UI.h"
#include "conio.h"
void StoreRoomScene::Start()
{
	Scene::Start();
	new Wall(Vector2(4, 2));
	new Wall(Vector2(5, 2));
	new Wall(Vector2(6, 2));
	new Wall(Vector2(7, 2));
	new Wall(Vector2(8, 2));
	new Wall(Vector2(3, 3));
	new Wall(Vector2(3, 4));
	new Wall(Vector2(3, 5));
	new Wall(Vector2(3, 6));
	new Wall(Vector2(4, 3));
	new Wall(Vector2(4, 6));
	new Wall(Vector2(4, 7));
	new Wall(Vector2(5, 7));
	new Wall(Vector2(6, 7));
	new Wall(Vector2(7, 7));
	new Wall(Vector2(8, 7));
	new Wall(Vector2(8, 6));
	new Wall(Vector2(8, 4));
	new Wall(Vector2(8, 3));
	new Furniture(Furniture::StoreRoomDoor, Vector2(8, 5));
	new Furniture(Furniture::Box, Vector2(5, 3));
	new Furniture(Furniture::EmptyBoxType1, Vector2(5, 6));
	new Furniture(Furniture::EmptyBoxType1, Vector2(6, 6));
	new Furniture(Furniture::EmptyBoxType1, Vector2(7, 6));
	new Furniture(Furniture::EmptyBoxType2, Vector2(4, 4));
	new Furniture(Furniture::EmptyBoxType2, Vector2(4, 5));
	new Furniture(Furniture::Planks, Vector2(6, 3));
	



	gm.CreatePlayer(Vector2(7, 5));

	UI gameUI(Vector2(130, 12));
	gameUI.CreateBox(Vector2(), "Inventory:", 40, 15);
	gameUI.CreateBox(Vector2(0, 17), "", 40, 10);

}

void StoreRoomScene::Update()
{
	Scene::Update();
}

