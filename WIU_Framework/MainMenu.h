#pragma once
#include "Scene.h"
#include "UI.h"
class MainMenu :
    public Scene
{
private:
    void DrawClock(const int size) const;
    
public:
    void Start(void) override;
    void Update(void) override;
    void Render(void) override;
    void Exit(void) override;
};

