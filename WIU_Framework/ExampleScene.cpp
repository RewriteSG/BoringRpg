#include "ExampleScene.h"
#include "SceneManager.h"
#include "Player.h"
void ExampleScene::Start()
{
	Scene::Start();
	// Instantiate Objects Here!

	// For Example 
	new Player();

}

void ExampleScene::Update()
{
	Scene::Update();

	// Update Game Here!
	//SceneManager::LoadScene(new Scene());
}
