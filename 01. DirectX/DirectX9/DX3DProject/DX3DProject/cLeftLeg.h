#pragma once
#include "cCubeNode.h"
class cLeftLeg :
    public cCubeNode
{
public:
    cLeftLeg();
    virtual ~cLeftLeg();

    virtual void Setup() override;
};

