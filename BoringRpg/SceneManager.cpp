#include "SceneManager.h"
#include "ExampleScene.h"
Scene* SceneManager::CurrentScene = nullptr;
Scene* SceneManager::nextScene = nullptr;

SceneManager::SceneManager()
{
	CurrentScene = new ExampleScene(); 
	nextScene = nullptr;
}

void SceneManager::Start()
{
	srand((unsigned int)time(0));
	CurrentScene->Start();
}

void SceneManager::Update()
{
	CurrentScene->Update();
	CurrentScene->Render();
	CurrentScene->gm.Update();
	if (nextScene) 
	{
		if (CurrentScene)
		{
			CurrentScene->Exit();
			delete CurrentScene;
		}
		CurrentScene = nullptr;
		CurrentScene = nextScene;
		nextScene = nullptr;
		system("cls");
		CurrentScene->Start();
	}
}

void SceneManager::LoadScene(Scene* toScene)
{
	nextScene = toScene;
	
}


void SceneManager::Exit()
{
	CurrentScene->Exit();
}