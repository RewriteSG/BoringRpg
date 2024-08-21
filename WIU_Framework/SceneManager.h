#pragma once
using namespace std;
#include "Scene.h"
class SceneManager
{
private:
	static std::string sceneName[];

	void DeleteScene(void);
public:
	enum SCENENAME
	{
		LIVING_ROOM,
		STOREROOM,
		TOILET,
		BEDROOM,
		KITCHEN,
		ENDINGS
	};

	static Scene* mainMenu;
	static Scene* endingsPage;

	static Scene* nextScene;
	static Scene* currentScene;
	static string prevScene; 
	SceneManager(void) = default;
	~SceneManager(void);
	void Start(void);
	void Update(void);
	void Exit(void);

	static void LoadScene(Scene* toScene);
	static void LoadScene(std::string toScene);
	static Scene* GetNextScene(void);

	static std::string GetSceneName(const SCENENAME type);
	static std::string GetSceneName(const int index);
};

