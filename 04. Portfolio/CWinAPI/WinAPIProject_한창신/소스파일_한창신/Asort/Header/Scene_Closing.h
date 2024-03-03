#pragma once
#include "CScene.h"
class Scene_Closing :
    public CScene
{

public:
    Scene_Closing();
    ~Scene_Closing();

    virtual void Enter();
    virtual void Exit();

};

