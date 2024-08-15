#pragma once
using namespace std;
#include "SceneManager.h"

class Application
{
private:
	SceneManager* sceneMgr;

private:
	void ScreenSMaximised(void);
	void HideCursor(void);
	void FontSize(const Vector2 size);
	
public:
	static int numberOfColumns;
	static int numberOfRows;
	Application(void);

	void Init(void);
	void Update(void);
	void Exit(void);
	
	static void DrawBG(void);
	
};

