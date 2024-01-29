#include "framework.h"
#include "cCubePNT.h"

cCubePNT::cCubePNT()
{
}

cCubePNT::~cCubePNT(void)
{
}

void cCubePNT::Setup()
{
	std::vector<ST_PNT_VERTEX> vecVertex;
	vecVertex.resize(8);

	//front 4 vertices
	vecVertex[0].p.x = -0.5f;	vecVertex[0].p.y = -0.5f;	vecVertex[0].p.z = -0.5f;
	vecVertex[1].p.x = -0.5f;	vecVertex[1].p.y = 0.5f;	vecVertex[1].p.z = -0.5f;
	vecVertex[2].p.x = 0.5f;	vecVertex[2].p.y = 0.5f;	vecVertex[2].p.z = -0.5f;
	vecVertex[3].p.x = 0.5f;	vecVertex[3].p.y = -0.5f;	vecVertex[3].p.z = -0.5f;
	// back 4 vertices
	vecVertex[4].p.x = -0.5f;	vecVertex[4].p.y = -0.5f;	vecVertex[4].p.z = 0.5f;
	vecVertex[5].p.x = -0.5f;	vecVertex[5].p.y = 0.5f;	vecVertex[5].p.z = 0.5f;
	vecVertex[6].p.x = 0.5f;	vecVertex[6].p.y = 0.5f;	vecVertex[6].p.z = 0.5f;
	vecVertex[7].p.x = 0.5f;	vecVertex[7].p.y = -0.5f;	vecVertex[7].p.z = 0.5f;

	std::vector<DWORD> vecIndex;
	// : front
	vecIndex.push_back(0); vecIndex.push_back(1); vecIndex.push_back(2);
	vecIndex.push_back(0); vecIndex.push_back(2); vecIndex.push_back(3);
	
	// : back
	vecIndex.push_back(4); vecIndex.push_back(6); vecIndex.push_back(5);
	vecIndex.push_back(4); vecIndex.push_back(7); vecIndex.push_back(6);

	// : left
	vecIndex.push_back(4); vecIndex.push_back(5); vecIndex.push_back(1);
	vecIndex.push_back(4); vecIndex.push_back(1); vecIndex.push_back(0);

	// : right
	vecIndex.push_back(3); vecIndex.push_back(2); vecIndex.push_back(6);
	vecIndex.push_back(3); vecIndex.push_back(6); vecIndex.push_back(7);

	// : top
	vecIndex.push_back(1); vecIndex.push_back(5); vecIndex.push_back(6);
	vecIndex.push_back(1); vecIndex.push_back(6); vecIndex.push_back(2);
	
	// : bottom
	vecIndex.push_back(4); vecIndex.push_back(0); vecIndex.push_back(3);
	vecIndex.push_back(4); vecIndex.push_back(3); vecIndex.push_back(7);

	m_vecVertex.resize(36);

	for (size_t i = 0; i < vecIndex.size(); i += 3)
	{
		m_vecVertex[i + 0] = vecVertex[vecIndex[i + 0]];
		m_vecVertex[i + 1] = vecVertex[vecIndex[i + 1]];
		m_vecVertex[i + 2] = vecVertex[vecIndex[i + 2]];
	}

	D3DXVECTOR3 u, v, n;

	//normal vector 구하기
	for (int i = 0; i < 36; i += 3)
	{
		u = m_vecVertex[i + 1].p - m_vecVertex[i + 0].p;
		v = m_vecVertex[i + 2].p - m_vecVertex[i + 0].p;
		D3DXVec3Cross(&n, &u, &v); //오른손 법칙
		D3DXVec3Normalize(&n, &n);
		
		m_vecVertex[i + 0].n = n;
		m_vecVertex[i + 1].n = n;
		m_vecVertex[i + 2].n = n;
	}
}

void cCubePNT::Update()
{
}

void cCubePNT::Render()
{
	DEVICE->SetFVF(ST_PNT_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PNT_VERTEX));
}
