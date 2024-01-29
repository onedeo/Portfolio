#pragma once
#include "cCubeNode.h"
class cBody : public cCubeNode
{
public:
	cBody();
	virtual ~cBody();

	virtual void Setup() override;

};

