#include "framework.h"
#include "cLeftLeg.h"

cLeftLeg::cLeftLeg()
{
}

cLeftLeg::~cLeftLeg()
{
}

void cLeftLeg::Setup()
{
	cCubeNode::Setup();

	cCubeNode::Setup();
	D3DXMATRIXA16 matS, matT, matW;
	D3DXMatrixScaling(&matS, 0.2f, 0.6f, 0.2f);
	D3DXMatrixTranslation(&matT, 0.f, 0.f, 0.f);
	matW = matS * matT;
	for (size_t i = 0; i < m_vecVertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &matW);
	}

	m_vLocalPos.y = -0.5f;
	m_vLocalPos.x = -0.1f;
}
