#include "ExampleScene.h"
#include "SceneManager.h"
#include "Player.h"
#include "Robber.h"

void ExampleScene::Start()
{
	Scene::Start();
	// Instantiate Objects Here!

	// For Example 
	new Player();
	new Robber(Vector2(2,2));


}

void ExampleScene::Update()
{
	Scene::Update();

	// Update Game Here!
	//SceneManager::LoadScene(new Scene());
}
