#pragma once
#include "cCubePNT.h"

class cCubeNode : public cCubePNT
{
public :
	cCubeNode();
	virtual ~cCubeNode();

	SYNTHESIZE(D3DXMATRIXA16*, m_pParentWorldTM, ParentWorldTM);
	SYNTHESIZE(float, m_fRotDeltaX, RotDeltaX);

	virtual void AddChild(cCubeNode* pChild);
	virtual void Destroy();

	virtual void Setup() override;
	virtual void Update() override;
	virtual void Render() override;

protected:
	D3DXVECTOR3			m_vLocalPos;
	D3DXMATRIXA16		m_matLocalTM;
	D3DXMATRIXA16		m_matWorldTM;
	std::vector<cCubeNode*> m_vecChild;
};

