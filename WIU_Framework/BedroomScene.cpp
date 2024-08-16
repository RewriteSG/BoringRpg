#include "BedroomScene.h"
#include "SceneManager.h"
#include "Player.h"
#include "Wall.h"
#include "Furniture.h"
#include "UI.h"
#include "conio.h"

BedroomScene::BedroomScene()
{
	name = "BEDROOM";
}

void BedroomScene::Start()
{
	Scene::Start();
	new Wall(Vector2(0, 0));
	new Wall(Vector2(0, 1));
	new Wall(Vector2(0, 2));
	new Wall(Vector2(0, 3));
	new Wall(Vector2(0, 4));
	new Wall(Vector2(0, 5));
	new Wall(Vector2(11, 0));
	new Wall(Vector2(11, 1));
	new Wall(Vector2(11, 2));
	new Wall(Vector2(11, 3));
	new Wall(Vector2(11, 4));
	new Wall(Vector2(1, 5));
	new Wall(Vector2(2, 5));
	new Wall(Vector2(3, 5));
	new Wall(Vector2(4, 5));
	new Wall(Vector2(6, 5));
	new Wall(Vector2(7, 5));
	new Wall(Vector2(8, 5));
	new Wall(Vector2(9, 5));
	new Wall(Vector2(10, 5));
	new Wall(Vector2(11, 5));
	//new Wall(Vector2(12, 5));
	//new Wall(Vector2(13, 5));
	//new Wall(Vector2(14, 5));
	new Wall(Vector2(1, 0));
	new Wall(Vector2(2, 0));
	new Wall(Vector2(3, 0));
	new Wall(Vector2(4, 0));
	new Wall(Vector2(5, 0));
	new Wall(Vector2(6, 0));
	new Wall(Vector2(7, 0));
	new Wall(Vector2(8, 0));
	new Wall(Vector2(9, 0));
	new Wall(Vector2(10, 0));
	new Wall(Vector2(11, 0));
	//new Wall(Vector2(12, 0));
	//new Wall(Vector2(13, 0));
	//new Wall(Vector2(14, 0));	
	new Furniture(Furniture::Bed, Vector2(1, 1));
	new Furniture(Furniture::Bed, Vector2(1, 2),true);
	new Furniture(Furniture::Bed, Vector2(2, 2), true);
	new Furniture(Furniture::BedroomCabinet1, Vector2(3, 1));
	new Furniture(Furniture::Bedroomtable, Vector2(5, 1));
	new Furniture(Furniture::Bedroomtable, Vector2(6, 1), true);
	new Furniture(Furniture::BedroomCabinet2, Vector2(10, 1));
	new Furniture(Furniture::BedroomCabinet2, Vector2(10, 2), true);
	new Furniture(Furniture::LivingRoomDoor, Vector2(5, 5));

	//if (draw.IsRobberDead == false) {

	////	gm.CreateRobber(Vector2(5, 8));
	//}
	gm.CreatePlayer(Vector2(5, 4));
}

void BedroomScene::Update()
{
	Scene::Update();
}
