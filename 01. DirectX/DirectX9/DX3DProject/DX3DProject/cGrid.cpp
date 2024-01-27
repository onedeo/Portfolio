#include "framework.h"
#include "cGrid.h"
#include "cGizmo.h"


cGrid::cGrid()
{
}

cGrid::~cGrid()
{
	for(auto p : m_vecGizmo)
	{
		SAFE_DELETE(p);
	}
	m_vecGizmo.clear();
}

void cGrid::Setup(int nNumHalfTile, float fInterval)
{
	float fMax = nNumHalfTile * fInterval;
	float fMin = -fMax;

	ST_PC_VERTEX v;
	for (int i = 1; i <= nNumHalfTile; i++)
	{
		if (i % 5 == 0) v.c = D3DCOLOR_XRGB(255, 255, 255);
		else v.c = D3DCOLOR_XRGB(128, 128, 128);

		v.p = D3DXVECTOR3(fMin, 0, i * fInterval); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, i * fInterval); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(fMin, 0, -i * fInterval); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, -i * fInterval); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(i * fInterval, 0, fMin); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(i * fInterval, 0, fMax); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-i * fInterval, 0, fMin); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-i * fInterval, 0, fMax); m_vecVertex.push_back(v);
	}

	//중간 x, y,z 축 선
	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(fMin, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(fMax, 0, 0); m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(0, fMin, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, fMax, 0); m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(0, 0, fMin); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, fMax); m_vecVertex.push_back(v);

	//축 피라미드
	cGizmo* pGizmo = NULL;
	D3DXMATRIXA16 matRotation;

	// x 축
	pGizmo = new cGizmo;
	D3DXMatrixRotationZ(&matRotation, D3DX_PI / 2.0f);
	pGizmo->Setup(D3DCOLOR_XRGB(255, 0, 0), matRotation);
	m_vecGizmo.push_back(pGizmo);
	// y 축
	pGizmo = new cGizmo;
	D3DXMatrixRotationZ(&matRotation, D3DX_PI);
	pGizmo->Setup(D3DCOLOR_XRGB(0, 255, 0), matRotation);
	m_vecGizmo.push_back(pGizmo);
	// z 축
	pGizmo = new cGizmo;
	D3DXMatrixRotationX(&matRotation, -D3DX_PI / 2.0f);
	pGizmo->Setup(D3DCOLOR_XRGB(0, 0, 255), matRotation);
	m_vecGizmo.push_back(pGizmo);

}

void cGrid::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	DEVICE->SetTransform(D3DTS_WORLD, &matWorld);

	DEVICE->SetFVF(ST_PC_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_LINELIST, m_vecVertex.size() / 2, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
	//LINELIST : vertex개수가 2의 배수형태로 있어야 그려준다 ST_PC_VERTEX단위로 짤라서 한 vertex를 읽어라

	for (auto p : m_vecGizmo)
	{
		p->Render();
	}
}
