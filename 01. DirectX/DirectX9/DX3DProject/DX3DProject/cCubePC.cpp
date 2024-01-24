#include "framework.h"
#include "cCubePC.h"

cCubePC::cCubePC()
	: m_vDirection(0.f, 0.f, 1.f)
	, m_vPosition(0.f,0.f,0.f)
	, m_fRotY(0.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cCubePC::~cCubePC()
{
}

void cCubePC::Setup()
{
	ST_PC_VERTEX v;

	// front
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, -1.0f);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, -1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -1.0f, -1.0f);	m_vecVertex.push_back(v);

	// back
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -1.0f, 1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);	m_vecVertex.push_back(v);

	// left
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);	m_vecVertex.push_back(v);

	// right
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(1.0f, -1.0f, -1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, -1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(1.0f, -1.0f, -1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -1.0f, 1.0f);	m_vecVertex.push_back(v);

	// top
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, -1.0f);	m_vecVertex.push_back(v);

	// bottom
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -1.0f, -1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -1.0f, 1.0f);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -1.0f, 1.0f);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);	m_vecVertex.push_back(v);
}

void cCubePC::Update()
{	
	if (GetKeyState('A') & 0x8000)
		m_fRotY -= 0.1f;
	if (GetKeyState('D') & 0x8000)
		m_fRotY += 0.1f;
	if (GetKeyState('W') & 0x8000)
		m_vPosition += (m_vDirection * 0.1f);
	if (GetKeyState('S') & 0x8000)
		m_vPosition -= (m_vDirection * 0.1f);

	D3DXMATRIXA16 matRotation, matTranslation;
	// rotation
	D3DXMatrixRotationY(&matRotation, m_fRotY);

	/*
	행렬
	a  b  c  d
	e  f  g  h
	i   j  k   l
	0 0  0  1
	이 주어 졌을 때
	1열의 a, e, i는 객체의 right 벡터
	2열의 b, f, j는 객체의 up vector
	3열의 c, g, k는 객체의 look vector다
	*/
	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matRotation);
	D3DXMatrixTranslation(&matTranslation, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	// S R T
	m_matWorld = matRotation * matTranslation;
}

void cCubePC::Render()
{
	DEVICE->SetTransform(D3DTS_WORLD, &m_matWorld);

	DEVICE->SetFVF(ST_PC_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PC_VERTEX));
}
