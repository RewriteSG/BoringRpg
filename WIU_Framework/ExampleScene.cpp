#include "ExampleScene.h"
#include "SceneManager.h"
#include "Player.h"
#include "UI.h"
#include "conio.h"
void ExampleScene::Start()
{
	UI gameUI(Vector2(130, 12));
	gameUI.CreateBox(Vector2(), "Inventory:", 40, 15);
	gameUI.CreateBox(Vector2(0, 17), "Dialogue:", 40, 10);

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
