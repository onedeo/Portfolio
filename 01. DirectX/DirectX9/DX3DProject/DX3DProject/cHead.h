#pragma once
#include "cCubeNode.h"
class cHead : public cCubeNode
{
public:
    cHead();
    virtual ~cHead();

    virtual void Setup() override;
};

