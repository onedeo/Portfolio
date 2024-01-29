#pragma once
#include "cCubeNode.h"
class cLeftArm :
    public cCubeNode
{
public:
    cLeftArm();
    virtual ~cLeftArm();

    virtual void Setup() override;
};

