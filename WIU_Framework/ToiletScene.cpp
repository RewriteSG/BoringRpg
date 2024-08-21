#include "ToiletScene.h"
#include "SceneManager.h"
#include "Player.h"
#include "Wall.h"
#include "Furniture.h"
#include "UI.h"
#include "conio.h"
#include "ToiletDoorSprite.h"
#include "Soap.h"
ToiletScene::ToiletScene(void)
{
	name = SceneManager::GetSceneName(SceneManager::TOILET);
}
void ToiletScene::Start()
{
	Scene::Start();
	soap = new Soap(gm.InteractionsMgr.soapPosition);
	soap->SetActive(gm.InteractionsMgr.isSoapSetup && gm.InteractionsMgr.soapLocation == name);
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

	Furniture* door = new Furniture(Furniture::LivingRoomDoor, Vector2(7, 2)); 
	door->SetSprite(new ToiletDoorSprite());
	new Furniture(Furniture::ShowerArea, Vector2(8, 5));
	new Furniture(Furniture::ToiletBowl, Vector2(5, 3));
	new Furniture(Furniture::ToiletCabinet, Vector2(5, 5));
	gm.CreatePlayer(Vector2(7, 3));
}

void ToiletScene::Update()
{
	Scene::Update();
}
