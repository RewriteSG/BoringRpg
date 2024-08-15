#include "SceneManager.h"
#include "ExampleScene.h"
#include "BedroomScene.h"
#include "Windows.h"
#include "MainMenu.h"
#include <cwchar>
#include "LivingRoomScene.h"
#include "ToiletScene.h"
#include "BedroomScene.h"

string SceneManager::prevScene = "nullptr";
Scene* SceneManager::currentScene = nullptr;
Scene* SceneManager::nextScene = nullptr;

void SceneManager::Start(void)
{
	srand((unsigned int)time(0));

	currentScene = new MainMenu();
	currentScene->Start();
}

void SceneManager::Update(void)
{
	currentScene->Update();
	currentScene->Render();

	MainMenu* menu = dynamic_cast<MainMenu*>(currentScene);
	if(!menu)
	currentScene->gm.Update();
	currentScene->Render(); 

	if (nextScene) 
	{
		if (currentScene)
		{
			currentScene->Exit();
			delete currentScene;
		}
		currentScene = nullptr;
		currentScene = nextScene;
		nextScene = nullptr;
		system("cls");
		currentScene->Start();
	}
}

void SceneManager::Exit() { currentScene->Exit(); }

void SceneManager::LoadScene(Scene* toScene) {
	if (dynamic_cast<LivingRoomScene*>(currentScene))
		prevScene = "LivingRoomScene";
	if (dynamic_cast<BedroomScene*>(currentScene)) 
		prevScene = "BedroomScene";
	if (dynamic_cast<ToiletScene*>(currentScene)) 
		prevScene = "ToiletScene";
	nextScene = toScene; 
}

void SceneManager::LoadScene(std::string toScene) {
	if (toScene == "LivingRoomScene")
		LoadScene(new LivingRoomScene());
	if(toScene == "BedroomScene")
		LoadScene(new BedroomScene());
	if(toScene == "ToiletScene")
		LoadScene(new ToiletScene());

}

Scene* SceneManager::GetNextScene(void) {return nextScene;}
