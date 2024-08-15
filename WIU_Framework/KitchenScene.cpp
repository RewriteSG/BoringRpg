#include "KitchenScene.h"
#include "SceneManager.h"
#include "Player.h"
#include "Wall.h"
#include "Furniture.h"
#include "UI.h"
#include "conio.h"
void KitchenScene::Start()
{
	Scene::Start();
	new Wall(Vector2(2, 1));
	new Wall(Vector2(2, 2));
	new Wall(Vector2(2, 4));
	new Wall(Vector2(2, 5));
	new Wall(Vector2(2, 6));
	new Wall(Vector2(11, 1));
	new Wall(Vector2(11, 2));
	new Wall(Vector2(11, 3));
	new Wall(Vector2(11, 4));
	new Wall(Vector2(11, 5));
	new Wall(Vector2(11, 6));
	
	new Wall(Vector2(2, 1));
	new Wall(Vector2(3, 1));
	new Wall(Vector2(4, 1));
	new Wall(Vector2(5, 1));
	new Wall(Vector2(6, 1));
	new Wall(Vector2(7, 1));
	new Wall(Vector2(8, 1));
	new Wall(Vector2(9, 1));
	new Wall(Vector2(10,1));
	new Wall(Vector2(2, 6));
	new Wall(Vector2(3, 6));
	new Wall(Vector2(4, 6));
	new Wall(Vector2(5, 6));
	new Wall(Vector2(6, 6));
	new Wall(Vector2(7, 6));
	new Wall(Vector2(8, 6));
	new Wall(Vector2(9, 6));
	new Wall(Vector2(10,6));
	new Furniture(Furniture::Sink, Vector2(4, 2));
	new Furniture(Furniture::KitchenTable, Vector2(6, 2));

	gm.CreatePlayer(Vector2(3, 3));

	UI gameUI(Vector2(130, 12));
	gameUI.CreateBox(Vector2(), "Inventory:", 40, 15);
	gameUI.CreateBox(Vector2(0, 17), "Dialogue:", 40, 10);

}

void KitchenScene::Update()
{
	Scene::Update();
}