#pragma once
using namespace std;
#include "Scene.h"
class SceneManager
{
private:

public:
	static Scene* nextScene;
	static Scene* currentScene;
	SceneManager(void) = default;
	static void Start(void);
	static void Update(void);
	static void Exit(void);

	static void LoadScene(Scene* toScene);
	static Scene* GetNextScene(void);
};

