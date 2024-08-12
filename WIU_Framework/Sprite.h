#pragma once
#include "Vector2.h"
class Sprite
{
public:
	Sprite();
	virtual void Render(int x, int y, Vector2 topLeft);
	static void RenderVoid(int x, int y, Vector2 topLeft);
};

