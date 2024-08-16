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
	new Wall(Vector2(0, 6));
	new Wall(Vector2(0, 7));
	new Wall(Vector2(0, 8));
	new Wall(Vector2(0, 9));
	new Wall(Vector2(14, 0));
	new Wall(Vector2(14, 1));
	new Wall(Vector2(14, 2));
	new Wall(Vector2(14, 3));
	new Wall(Vector2(14, 4));
	new Wall(Vector2(14, 5));
	new Wall(Vector2(14, 6));
	new Wall(Vector2(14, 7));
	new Wall(Vector2(14, 8));
	new Wall(Vector2(14, 9));
	new Wall(Vector2(1, 9));
	new Wall(Vector2(2, 9));
	new Wall(Vector2(3, 9));
	new Wall(Vector2(4, 9));
	new Wall(Vector2(6, 9));
	new Wall(Vector2(7, 9));
	new Wall(Vector2(8, 9));
	new Wall(Vector2(9, 9));
	new Wall(Vector2(10, 9));
	new Wall(Vector2(11, 9));
	new Wall(Vector2(12, 9));
	new Wall(Vector2(13, 9));
	new Wall(Vector2(14, 9));
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
	new Wall(Vector2(12, 0));
	new Wall(Vector2(13, 0));
	new Wall(Vector2(14, 0));	
	new Furniture(Furniture::Bed, Vector2(1, 1));
	new Furniture(Furniture::Bed, Vector2(1, 2),true);
	new Furniture(Furniture::Bed, Vector2(2, 2), true);
	new Furniture(Furniture::BedroomCabinet1, Vector2(3, 1));
	new Furniture(Furniture::Bedroomtable, Vector2(5, 1));
	new Furniture(Furniture::Bedroomtable, Vector2(6, 1), true);
	new Furniture(Furniture::BedroomCabinet2, Vector2(13, 1));
	new Furniture(Furniture::BedroomCabinet2, Vector2(13, 2), true);
	new Furniture(Furniture::LivingRoomDoor, Vector2(5, 9));

	if (draw.IsRobberDead == false) {

		gm.CreateRobber(Vector2(5, 8));
	}
	gm.CreatePlayer(Vector2(5, 8));
}

void BedroomScene::Update()
{
	Scene::Update();
}
