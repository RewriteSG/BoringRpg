#include "ExampleScene.h"
#include "SceneManager.h"
#include "Player.h"
#include "UI.h"
void ExampleScene::Start()
{
	Scene::Start();
	// Instantiate Objects Here!

	// For Example 
	new Player();

	//robber
	new Robber();

}

void ExampleScene::Update()
{
	Scene::Update();

	UI ui(Vector2(130, 10));
	ui.CreateDialogueUI("Dialogue: ", 112, 40, 10);
	ui.GetDialogueUI()->PrintDialogue(Vector2(), Player::playerInstance, "is a person");

	// Update Game Here!
	//SceneManager::LoadScene(new Scene());
}
