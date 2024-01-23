#include "cDeviceManager.h"

cDeviceManager::cDeviceManager() :m_pD3D(NULL), m_pD3DDevice(NULL)
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 stCaps;
	int nVertexProcessing;
	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &stCaps);
	if (stCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		// 다른 하드웨어에서 계산
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		// CPU에서 계산
		nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	D3DPRESENT_PARAMETERS stD3DPP;
	ZeroMemory(&stD3DPP, sizeof(D3DPRESENT_PARAMETERS));
	stD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	stD3DPP.Windowed = TRUE; // 개발 단계에서는 보통 윈도우로 확인하고 풀스크린으로 테스트 한다
	stD3DPP.BackBufferFormat = D3DFMT_UNKNOWN;
	stD3DPP.EnableAutoDepthStencil = TRUE;
	stD3DPP.AutoDepthStencilFormat = D3DFMT_D16;

	m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, nVertexProcessing, &stD3DPP, &m_pD3DDevice);
}

cDeviceManager::~cDeviceManager()
{

}

void cDeviceManager::Destroy()
{
	SAFE_RELEASE(m_pD3D);
	SAFE_RELEASE(m_pD3DDevice);
}
