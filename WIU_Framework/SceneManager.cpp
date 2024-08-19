#include "SceneManager.h"
#include "ExampleScene.h"
#include "BedroomScene.h"
#include "Windows.h"
#include "MainMenu.h"
#include "LivingRoomScene.h"
#include "ToiletScene.h"
#include "BedroomScene.h"
#include "StoreRoomScene.h"
#include "KitchenScene.h"
#include "Endings.h"
#include <cwchar>

string SceneManager::prevScene = "nullptr";
Scene* SceneManager::currentScene = nullptr;
Scene* SceneManager::nextScene = nullptr;
std::string SceneManager::sceneName[6] = { "LIVING ROOM", "TOILET", "STOREROOM", "BEDROOM", "KITCHEN", "ENDINGS"};

void SceneManager::Start(void)
{
	srand((unsigned int)time(0));

	currentScene = new MainMenu();
	currentScene->Start();
}

void SceneManager::Update(void)
{

	currentScene->Update();


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
	if (dynamic_cast<StoreRoomScene*>(currentScene))
		prevScene = "StoreRoomScene";
	if (dynamic_cast<KitchenScene*>(currentScene))
		prevScene = "KitchenScene";
	if (dynamic_cast<Endings*>(currentScene))
		prevScene = "EndingsScene";
	nextScene = toScene;
}

void SceneManager::LoadScene(std::string toScene) {
	if (toScene == "LivingRoomScene")
		LoadScene(new LivingRoomScene());
	if (toScene == "BedroomScene")
		LoadScene(new BedroomScene());
	if (toScene == "ToiletScene")
		LoadScene(new ToiletScene());
	if (toScene == "StoreRoomScene")
		LoadScene(new StoreRoomScene());
	if(toScene == "KitchenScene")
		LoadScene(new KitchenScene());
	if (toScene == "EndingsScene")
		LoadScene(new Endings());

}
Scene* SceneManager::GetNextScene(void) {return nextScene;}

std::string SceneManager::GetSceneName(const SCENENAME type)
{
	return sceneName[type];
}

std::string SceneManager::GetSceneName(const int index)
{
	return sceneName[index];
}
