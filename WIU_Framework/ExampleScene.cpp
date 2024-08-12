#include "ExampleScene.h"
#include "SceneManager.h"
void ExampleScene::Start()
{
	Scene::Start();
	// Instantiate Objects Here!

	// For Example 
	new Entity(Vector2(4, 4));

}

void ExampleScene::Update()
{
	Scene::Update();

	// Update Game Here!
	//SceneManager::LoadScene(new Scene());
}
