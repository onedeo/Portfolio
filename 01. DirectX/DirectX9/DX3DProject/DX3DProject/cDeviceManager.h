#pragma once
#include "framework.h"

#define DEVICE_MANAGER			cDeviceManager::GetInstance()
#define DEVICE							DEVICE_MANAGER->GetDevice()

class cDeviceManager
{	
	SINGLETON(cDeviceManager);

private :
	LPDIRECT3D9						m_pD3D;
	LPDIRECT3DDEVICE9			m_pD3DDevice;

public :
	LPDIRECT3DDEVICE9 GetDevice() { return m_pD3DDevice; }
	void Destroy();
};

