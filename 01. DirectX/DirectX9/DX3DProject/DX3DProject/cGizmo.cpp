#include "framework.h"
#include "cGizmo.h"

cGizmo::cGizmo()
{
	D3DXMatrixIdentity(&m_matRotation);
}

cGizmo::~cGizmo()
{
}

void cGizmo::Setup(D3DCOLOR color, D3DXMATRIXA16& matrix)
{
	m_matRotation = matrix;

	ST_PC_VERTEX v;
	v.c = color;

	//front
	v.p = D3DXVECTOR3(0.f, 0.f, 0.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, -1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, -1.f, -1.f); m_vecVertex.push_back(v);

	//back
	v.p = D3DXVECTOR3(0.f, 0.f, 0.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, -1.f, 1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, 1.f); m_vecVertex.push_back(v);

	//right
	v.p = D3DXVECTOR3(0.f, 0.f, 0.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, 1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, -1.f); m_vecVertex.push_back(v);

	//left
	v.p = D3DXVECTOR3(0.f, 0.f, 0.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, -1.f, -1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, -1.f, 1.f); m_vecVertex.push_back(v);

	//bottom
	v.p = D3DXVECTOR3(-1.f, -1.f, -1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, -1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, 1.f); m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.f, -1.f, -1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.f, -1.f, 1.f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.f, -1.f, 1.f); m_vecVertex.push_back(v);
}

void cGizmo::Render()
{
	D3DXMATRIXA16 matWorld, matScale;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 0.1f, 2.0f, 0.1f);

	matWorld = matScale * m_matRotation;

	DEVICE->SetTransform(D3DTS_WORLD, &matWorld);

	DEVICE->SetFVF(ST_PC_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
}
