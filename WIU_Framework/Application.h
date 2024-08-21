#pragma once
using namespace std;
#include "SceneManager.h"

class Application
{
private:
	SceneManager* sceneMgr;

private:
	void ScreenMaximised(void);
	void FontSize(const Vector2 size);
	
public:
	static int numberOfColumns;
	static int numberOfRows;
	Application(void) = default;

	void Init(void);
	void Update(void);
	void Exit(void);

	static void HideCursor(void);
	static void ShowCursor(void);
};

