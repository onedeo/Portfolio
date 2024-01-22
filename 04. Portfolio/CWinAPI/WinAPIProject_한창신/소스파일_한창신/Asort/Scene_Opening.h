#pragma once
#include "CScene.h"
class Scene_Opening :
    public CScene
{
private:


public:
    Scene_Opening();
    ~Scene_Opening();

    virtual void Enter();
    virtual void Exit();
};

