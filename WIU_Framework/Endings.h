#pragma once
#include "Scene.h"
class Endings :
    public Scene
{
    public:
        Endings();
        void Start() override;
        void Update() override;
        void ending1();
        void ending2();
        void ending3();
        void ending4();
        void ending5();
        bool isunlocked[5];
      
  
};

