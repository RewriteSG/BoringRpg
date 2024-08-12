#pragma once
#include "GameObject.h"
class Item :
    public GameObject
{
    int id;
public:
    Item();
    int GetID() const;
    void SetID(int toId);
};

