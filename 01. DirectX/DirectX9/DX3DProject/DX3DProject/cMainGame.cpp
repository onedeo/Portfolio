#include "framework.h" //"'는 사용자가 등록한 위치 먼저 찾으라는 뜻
#include "cMainGame.h"

cMainGame::cMainGame()
{
}

cMainGame::~cMainGame()
{
	DEVICE_MANAGER->Destroy();
}

void cMainGame::Setup()
{
	Setup_Line();
	Setup_Triangle();
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
}

void cMainGame::Update()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	//eye matrix
	D3DXVECTOR3 vEye = D3DXVECTOR3(0, 0, -5.0f);
	D3DXVECTOR3 vLookAt = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 vUp = D3DXVECTOR3(0, 1, 0);
	
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEye, &vLookAt, &vUp);
	DEVICE->SetTransform(D3DTS_VIEW, &matView);

	//projection matrix
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	DEVICE->SetTransform(D3DTS_PROJECTION, &matProj);
}

void cMainGame::Render()
{
	DEVICE->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	DEVICE->BeginScene();

	Draw_Line();
	Draw_Triangle();

	DEVICE->EndScene();

	DEVICE->Present(NULL, NULL, NULL, NULL);

}

void cMainGame::Setup_Line()
{
	ST_PC_VERTEX		v;
	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(0, 2.f, 0);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(0, -2.f, 0);
	m_vecLineVertex.push_back(v);
}

void cMainGame::Draw_Line()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	DEVICE->SetTransform(D3DTS_WORLD, &matWorld);

	DEVICE->SetFVF(ST_PC_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_LINELIST, m_vecLineVertex.size() / 2, &m_vecLineVertex[0], sizeof(ST_PC_VERTEX));
		//LINELIST : vertex개수가 2의 배수형태로 있어야 그려준다 ST_PC_VERTEX단위로 짤라서 한 vertex를 읽어라
}

void cMainGame::Setup_Triangle()
{
	ST_PC_VERTEX	v;
	// 1 2
	// 0
	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(-1.0f, -1.0f, 0);
	m_vecTriangleVertex.push_back(v);
	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(-1.0f, 1.0f, 0);
	m_vecTriangleVertex.push_back(v);
	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(1.0f, 1.0f, 0);
	m_vecTriangleVertex.push_back(v);
}

void cMainGame::Draw_Triangle()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	//D3DXVECTOR3 translation(2, 0, 0);
	//D3DXMatrixTranslation(&matWorld, translation.x, translation.y, translation.z);
	DEVICE->SetTransform(D3DTS_WORLD, &matWorld);

	DEVICE->SetFVF(ST_PC_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecTriangleVertex.size() / 3, &m_vecTriangleVertex[0], sizeof(ST_PC_VERTEX));
}
