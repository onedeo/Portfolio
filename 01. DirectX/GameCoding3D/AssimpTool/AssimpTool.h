#pragma once
#include "IExecute.h"

class AssimpTool : public IExecute
{
public:
	// IExecute��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

