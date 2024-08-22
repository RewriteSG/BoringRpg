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
     static bool isunlocked[5];

     enum ENDINGTYPE
     {
         GOT_KILLED,
         SUICIDE,
         ARRESTED,
         KILLER_KILLED,
         SLEEPING,
     };

     void ShowEnding(const int type);
};

