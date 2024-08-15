#include "SceneManager.h"
#include "ExampleScene.h"
#include "BedroomScene.h"
#include "LivingRoomScene.h"
#include "Windows.h"
#include "MainMenu.h"
#include <cwchar>
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

void SceneManager::LoadScene(Scene* toScene) { nextScene = toScene; }

Scene* SceneManager::GetNextScene(void) {return nextScene;}
