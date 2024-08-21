#include "LivingRoomScene.h"
#include "SceneManager.h"
#include "Player.h"
#include "Wall.h"
#include "Furniture.h"
#include "Robber.h"
#include "UI.h"
#include "conio.h"
#include "Soap.h"
LivingRoomScene::LivingRoomScene(void)
{
	name = SceneManager::GetSceneName(SceneManager::LIVING_ROOM);
}
void LivingRoomScene::Start()
{
	Scene::Start();
	soap =	new Soap(gm.InteractionsMgr.soapPosition);
	soap->SetActive(gm.InteractionsMgr.isSoapSetup && gm.InteractionsMgr.soapLocation == name);
	new Furniture(Furniture::Clock, Vector2(9, 0));
	new Wall(Vector2(0, 0));
	new Wall(Vector2(0, 1));
	new Wall(Vector2(0, 2));
	new Wall(Vector2(0, 5));
	new Wall(Vector2(0, 4));
	new Wall(Vector2(0, 6));
	new Wall(Vector2(0, 7));

	new Wall(Vector2(12, 0));
	new Wall(Vector2(12, 1));
	new Wall(Vector2(12, 3));
	new Wall(Vector2(12, 4));
	new Wall(Vector2(12, 5));
	new Wall(Vector2(1, 7));
	new Wall(Vector2(2, 7));
	new Wall(Vector2(3, 7));
	new Wall(Vector2(4, 7));
	new Wall(Vector2(5, 7));
	new Wall(Vector2(6, 7));
	new Wall(Vector2(7, 7));
	new Wall(Vector2(8, 7));
	new Wall(Vector2(10, 7));
	new Wall(Vector2(11, 7));
	new Wall(Vector2(12, 7));
	/*new Wall(Vector2(12, 8));*/
	new Wall(Vector2(12, 5));
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
	//new Wall(Vector2(13, 0));
	//new Wall(Vector2(14, 0));
	new Furniture(Furniture::LivingRoomCabinet, Vector2(1, 1));
	new Furniture(Furniture::Television, Vector2(3, 1));
	new Furniture(Furniture::Television, Vector2(4, 1), true);
	new Furniture(Furniture::LivingroomTable, Vector2(2, 4));
	new Furniture(Furniture::LivingroomTable, Vector2(3, 4), true);
	new Furniture(Furniture::LivingroomTable, Vector2(4, 4), true);
	new Furniture(Furniture::LivingroomTable, Vector2(5, 4), true);
	new Furniture(Furniture::LivingroomTable, Vector2(6, 4), true);
	new Furniture(Furniture::LivingroomTable, Vector2(7, 5), true);
	new Furniture(Furniture::LivingroomTable, Vector2(7, 4), true);
	new Furniture(Furniture::LivingroomTable, Vector2(7, 5), true);
	new Furniture(Furniture::EmptySofa, Vector2(1, 4));
	new Furniture(Furniture::SofaKey, Vector2(7, 6),true);
	new Furniture(Furniture::BedRoomDoor, Vector2(8, 0));
	new Furniture(Furniture::StoreRoomDoor, Vector2(0, 3));
	new Furniture(Furniture::ToiletDoor, Vector2(9, 7));
	new Furniture(Furniture::KitchenDoor, Vector2(12, 2));
	new Furniture(Furniture::MainDoor, Vector2(12, 6));

	gm.CreatePlayer(Vector2(11, 6));
	
	//gm.CreateRobber(Vector2(5, 3));
}

void LivingRoomScene::Update()
{
	Scene::Update();
}

