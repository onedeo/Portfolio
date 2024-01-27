#include "framework.h" //"'는 사용자가 등록한 위치 먼저 찾으라는 뜻
#include "cMainGame.h"
#include "cCubePC.h"
#include "cCamera.h"
#include "cGrid.h"

cMainGame::cMainGame() : m_pCubePC(NULL), m_pCamera(NULL)
{
	srand(time(0));
}

cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pCubePC);
	SAFE_DELETE(m_pGrid);

	DEVICE_MANAGER->Destroy();
}

void cMainGame::Setup()
{
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
	//Setup_Line();
	//Setup_Triangle();
	
	m_pCubePC = new cCubePC();
	m_pCubePC->Setup();

	m_pCamera = new cCamera();
	//m_pCamera->Setup(&m_pCubePC->GetPosition());
	m_pCamera->Setup();

	m_pGrid = new cGrid();
	m_pGrid->Setup();
}

void cMainGame::Update()
{
	if (m_pCubePC)
		m_pCubePC->Update();
	if (m_pCamera)
		m_pCamera->Update();
}

void cMainGame::Render()
{
	DEVICE->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	DEVICE->BeginScene();

	//Draw_Line();
	//Draw_Triangle();
	
	if (m_pGrid)	m_pGrid->Render();
	if (m_pCubePC) m_pCubePC->Render();

	DEVICE->EndScene();

	DEVICE->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
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
	D3DXVECTOR3 translation(-5, 0, 0);
	D3DXMatrixTranslation(&matWorld, translation.x, translation.y, translation.z);
	DEVICE->SetTransform(D3DTS_WORLD, &matWorld);

	DEVICE->SetFVF(ST_PC_VERTEX::FVF); //flexible vertex format
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecTriangleVertex.size() / 3, &m_vecTriangleVertex[0], sizeof(ST_PC_VERTEX));
}
