#pragma once
#include "Sprite.h"
class RobberSprite :
    public Sprite
{
    void Render(int x, int y, Vector2 topleft) override;

};

