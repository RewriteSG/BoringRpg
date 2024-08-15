#pragma once
#include "Sprite.h"
class BoxSprite :
    public Sprite
{

    void Render(int x, int y, Vector2 topLeft) override;

};

