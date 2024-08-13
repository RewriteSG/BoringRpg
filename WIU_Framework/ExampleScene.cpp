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

}

void ExampleScene::Update()
{
	Scene::Update();

	UI ui(Vector2(130, 10));
	ui.CreateDialogueUI(112);
	ui.GetDialogueUI()->PrintDialogue(Vector2(), Player::playerInstance, "is a  gayest person");

	// Update Game Here!
	//SceneManager::LoadScene(new Scene());
}
