#include "SceneManager.h"

SceneManager::SceneManager()
{
	CurrentScene = new Scene(); 
	nextScene = nullptr;
}

void SceneManager::Start()
{
	srand((unsigned int)time(0));
	CurrentScene->Start();
	Exit();
}

void SceneManager::Update()
{
	CurrentScene->Render();
	CurrentScene->Update();
	CurrentScene->Render();

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