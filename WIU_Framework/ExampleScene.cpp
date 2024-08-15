#include "ExampleScene.h"
#include "SceneManager.h"
#include "Player.h"
#include "UI.h"
#include "conio.h"
void ExampleScene::Start()
{
	UI gameUI(Vector2(130, 12));
	gameUI.CreateBox(Vector2(), "Inventory:", 40, 5);
	gameUI.CreateBox(Vector2(0, 17), " ", 40, 20);

	new Player();

	//robber
	new Robber();

	Scene::Start();


}

void ExampleScene::Update()
{
	Scene::Update();

	// Update Game Here!
	//SceneManager::LoadScene(new Scene());
}
