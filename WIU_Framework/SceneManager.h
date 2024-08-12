#pragma once
using namespace std;
#include "Scene.h"
class SceneManager
{
private:
	static Scene* nextScene;
	static Scene* currentScene;

public:
	SceneManager(void) = default;
	static void Start(void);
	static void Update(void);
	static void Exit(void);

	static void LoadScene(Scene* toScene);
	static Scene* GetNextScene(void);
};

