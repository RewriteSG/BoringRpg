#include "KitchenScene.h"
#include "SceneManager.h"
#include "Player.h"
#include "Wall.h"
#include "Furniture.h"
#include "UI.h"
#include "conio.h"
KitchenScene::KitchenScene(void)
{
	name = SceneManager::GetSceneName(SceneManager::KITCHEN);
}
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
	new Furniture(Furniture::KitchenCabinet, Vector2(8, 5));
	new Furniture(Furniture::Stove, Vector2(7, 5));
	new Furniture(Furniture::Stove, Vector2(6, 5));
	new Furniture(Furniture::TrashCan, Vector2(5, 5));
	new Furniture(Furniture::Fridge, Vector2(3, 5));

	gm.CreatePlayer(Vector2(3, 3));
}

void KitchenScene::Update()
{
	Scene::Update();
}