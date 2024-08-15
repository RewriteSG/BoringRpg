#pragma once
#include "Sprite.h"
class RobberDownSprite :
    public Sprite
{
    void Render(int x, int y, Vector2 topleft) override;
};

