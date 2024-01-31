#include "framework.h" //"'는 사용자가 등록한 위치 먼저 찾으라는 뜻
#include "cMainGame.h"
#include "cCubePC.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cCubeMan.h"

cMainGame::cMainGame()
	: m_pCubePC(NULL)
	, m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pCubeMan(NULL)
	, m_pTexture(NULL)
{
	srand(time(0));
}

cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pCubePC);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pCubeMan);

	SAFE_RELEASE(m_pTexture);

	DEVICE_MANAGER->Destroy();
}

void cMainGame::Setup()
{
	//Setup_Line();
	//Setup_Triangle();
	//Cube
	/*m_pCubePC = new cCubePC();
	m_pCubePC->Setup();*/

	//CubeMan
	m_pCubeMan = new cCubeMan();
	m_pCubeMan->Setup();

	//camera
	m_pCamera = new cCamera();
	m_pCamera->Setup(&m_pCubeMan->GetPosition());
	//m_pCamera->Setup();

	m_pGrid = new cGrid();
	m_pGrid->Setup();

	Setup_Light();
	Setup_Texture();

	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
}

void cMainGame::Update()
{
	if (m_pCubePC)
		m_pCubePC->Update();
	if (m_pCamera)
		m_pCamera->Update();
	if (m_pCubeMan)
		m_pCubeMan->Update();
}

void cMainGame::Render()
{
	DEVICE->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	DEVICE->BeginScene();

	//Draw_Line();
	//Draw_Triangle();
	Draw_Texture();

	if (m_pGrid)	m_pGrid->Render();
	//if (m_pCubePC) m_pCubePC->Render();
	if (m_pCubeMan) m_pCubeMan->Render();

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

void cMainGame::Setup_Light()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	D3DXVECTOR3 vDir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	DEVICE->SetLight(0, &stLight);
	DEVICE->LightEnable(0, true);
}

void cMainGame::Setup_Texture()
{
	D3DXCreateTextureFromFile(DEVICE, L"../Image/faker.jpeg", &m_pTexture);
	ST_PT_VERTEX v;

	v.p = D3DXVECTOR3(0, 0, 0);
	v.t = D3DXVECTOR2(0, 1);
	m_vecTexVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 7, 0);
	v.t = D3DXVECTOR2(0, 0);
	m_vecTexVertex.push_back(v);

	v.p = D3DXVECTOR3(5, 7, 0);
	v.t = D3DXVECTOR2(1, 0);
	m_vecTexVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 0, 0);
	v.t = D3DXVECTOR2(0, 1);
	m_vecTexVertex.push_back(v);

	v.p = D3DXVECTOR3(5, 7, 0);
	v.t = D3DXVECTOR2(1, 0);
	m_vecTexVertex.push_back(v);

	v.p = D3DXVECTOR3(5, 0, 0);
	v.t = D3DXVECTOR2(1, 1);
	m_vecTexVertex.push_back(v);


	// 반대편
	v.p = D3DXVECTOR3(0, 0, 0);
	v.t = D3DXVECTOR2(0, 1);
	m_vecTexVertex.push_back(v);

	v.p = D3DXVECTOR3(-2, 2, 0);
	v.t = D3DXVECTOR2(1, 0);
	m_vecTexVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 2, 0);
	v.t = D3DXVECTOR2(0, 0);
	m_vecTexVertex.push_back(v);

}

void cMainGame::Draw_Texture()
{
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	DEVICE->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	DEVICE->SetTransform(D3DTS_WORLD, &matWorld);
	DEVICE->SetTexture(0, m_pTexture);
	
	DEVICE->SetFVF(ST_PT_VERTEX::FVF);
	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecTexVertex.size() / 3, &m_vecTexVertex[0], sizeof(ST_PT_VERTEX));
	
	//한개의 texture적용하고 나서 더이상 적용 안할거면 NULL로 세팅 해줘야 한다
	DEVICE->SetTexture(0, NULL);
}
