#include "KitchenScene.h"
#include "SceneManager.h"
#include "Player.h"
#include "Wall.h"
#include "Furniture.h"
#include "UI.h"
#include "conio.h"
#include "StoreRoomDoorSprite.h"
#include "Soap.h"
KitchenScene::KitchenScene(void)
{
	name = SceneManager::GetSceneName(SceneManager::KITCHEN);
}
void KitchenScene::Start()
{
	Scene::Start();
	soap = new Soap(gm.InteractionsMgr.soapPosition);
	soap->SetActive(gm.InteractionsMgr.isSoapSetup && gm.InteractionsMgr.soapLocation == name);
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
	new Furniture(Furniture::Sink, Vector2(5, 2), true);
	new Furniture(Furniture::KitchenTable, Vector2(6, 2));
	new Furniture(Furniture::KitchenTable, Vector2(7, 2),true);
	new Furniture(Furniture::KitchenTable, Vector2(8, 2), true); 
	new Furniture(Furniture::KitchenTable, Vector2(9, 2), true);
	new Furniture(Furniture::KitchenTable, Vector2(10, 2), true);
	new Furniture(Furniture::KitchenTable, Vector2(10, 2), true);
	new Furniture(Furniture::KitchenTable, Vector2(10, 3), true); 
	new Furniture(Furniture::KitchenTable, Vector2(10, 4), true); 
	new Furniture(Furniture::KitchenTable, Vector2(10, 5), true); 
	new Furniture(Furniture::KitchenCabinet, Vector2(8, 5)); 
	new Furniture(Furniture::KitchenCabinet, Vector2(9, 5),true);
	new Furniture(Furniture::Stove, Vector2(7, 5));
	new Furniture(Furniture::Stove, Vector2(6, 5));
	new Furniture(Furniture::TrashCan, Vector2(5, 5));
	new Furniture(Furniture::Fridge, Vector2(3, 5)); 
	new Furniture(Furniture::Fridge, Vector2(4, 5), true);
	Furniture* door = new Furniture(Furniture::LivingRoomDoor, Vector2(2, 3));
	door->SetSprite(new StoreRoomDoorSprite());
	gm.CreatePlayer(Vector2(3, 3));
}

void KitchenScene::Update()
{
	Scene::Update();
}