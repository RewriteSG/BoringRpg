#include "ExampleScene.h"
#include "SceneManager.h"
#include "Player.h"
#include "UI.h"
#include "conio.h"
void ExampleScene::Start()
{

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
