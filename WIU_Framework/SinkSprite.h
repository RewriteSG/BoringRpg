#pragma once
#include "Sprite.h"
class SinkSprite :
    public Sprite
{

    void Render(int x, int y, Vector2 topLeft) override;

};

