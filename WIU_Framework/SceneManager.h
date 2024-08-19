#pragma once
using namespace std;
#include "Scene.h"
class SceneManager
{
private:
	static std::string sceneName[];
public:
	enum SCENENAME
	{
		LIVING_ROOM,
		TOILET,
		STOREROOM,
		BEDROOM,
		KITCHEN,
	};

	static Scene* nextScene;
	static Scene* currentScene;
	static string prevScene; 
	SceneManager(void) = default;
	static void Start(void);
	static void Update(void);
	static void Exit(void);

	static void LoadScene(Scene* toScene);
	static void LoadScene(std::string toScene);
	static Scene* GetNextScene(void);

	static std::string GetSceneName(const SCENENAME type);
	static std::string GetSceneName(const int index);
};

