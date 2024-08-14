#include "LivingRoomScene.h"
#include "SceneManager.h"
#include "Player.h"
#include "Wall.h"
#include "Furniture.h"
#include "PickupableItem.h"
void LivingRoomScene::Start()
{
	Scene::Start();
	new Wall(Vector2(0, 0));
	new Wall(Vector2(0, 1));
	new Wall(Vector2(0, 2));
	new Wall(Vector2(0, 5));
	new Wall(Vector2(0, 4));
	new Wall(Vector2(0, 6));
	new Wall(Vector2(0, 7));
	
	new Wall(Vector2(14, 0));
	new Wall(Vector2(14, 1));
	new Wall(Vector2(14, 3));
	new Wall(Vector2(14, 4));
	new Wall(Vector2(14, 5));
	new Wall(Vector2(12, 6));
	new Wall(Vector2(1, 7));
	new Wall(Vector2(2, 7));
	new Wall(Vector2(3, 7));
	new Wall(Vector2(4, 7));
	new Wall(Vector2(5, 7));
	new Wall(Vector2(6, 7));
	new Wall(Vector2(7, 7));
	new Wall(Vector2(8, 7));
	new Wall(Vector2(9, 7));
	new Wall(Vector2(11, 7));
	new Wall(Vector2(12, 7));
	/*new Wall(Vector2(12, 8));*/
	new Wall(Vector2(12, 5));
	new Wall(Vector2(13, 5));
	new Wall(Vector2(14, 5));
	new Wall(Vector2(1, 0));
	new Wall(Vector2(2, 0));
	new Wall(Vector2(3, 0));
	new Wall(Vector2(4, 0));
	new Wall(Vector2(5, 0));
	new Wall(Vector2(6, 0));
	new Wall(Vector2(7, 0));
	new Wall(Vector2(9, 0));
	new Wall(Vector2(10, 0));
	new Wall(Vector2(11, 0));
	new Wall(Vector2(12, 0));
	new Wall(Vector2(13, 0));
	new Wall(Vector2(14, 0));
	new PickupableItem(PickupableItem::Knife, Vector2(7, 4)); 
	new Furniture(Furniture::LivingRoomCabinet, Vector2(1, 1));
	new Furniture(Furniture::Television, Vector2(3, 1));
	new Furniture(Furniture::Television, Vector2(4, 1),true);
	new Furniture(Furniture::LivingroomTable, Vector2(2, 4));
	new Furniture(Furniture::LivingroomTable, Vector2(3, 4), true);
	new Furniture(Furniture::LivingroomTable, Vector2(4, 4), true);
	new Furniture(Furniture::LivingroomTable, Vector2(5, 4), true);
	new Furniture(Furniture::LivingroomTable, Vector2(6, 4), true);
	new Furniture(Furniture::LivingroomTable, Vector2(7, 5), true);
	new Furniture(Furniture::EmptySofa, Vector2(1, 4));

	gm.CreatePlayer(Vector2(11, 6));
}

void LivingRoomScene::Update()
{
	Scene::Update();
}

