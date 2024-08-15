#pragma once
#include "Sprite.h"
class ClockSprite :
    public Sprite
{
public:
    void Render(int x, int y, Vector2 topLeft) override;
};

