#include "ToiletScene.h"
#include "SceneManager.h"
#include "Player.h"
#include "Wall.h"
#include "Furniture.h"

void ToiletScene::Start()
{
	Scene::Start();
	new Wall(Vector2(0, 0));
	new Wall(Vector2(0, 1));
	new Wall(Vector2(0, 2));
	new Wall(Vector2(0, 3));
	new Wall(Vector2(0, 4));
	

}

void ToiletScene::Update()
{
	Scene::Update();
}