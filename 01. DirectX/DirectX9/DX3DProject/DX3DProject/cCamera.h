#pragma once
class cCamera
{
public:
	cCamera();
	~cCamera();

	void Setup(D3DXVECTOR3* pvTarget = NULL);
	void Update();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;
	D3DXVECTOR3*		m_pvTarget;

	POINT						m_ptPrevMouse;
	bool							m_isLButtonDown;
	float							m_fCameraDistance;
	D3DXVECTOR3		m_vCamRotAngle;
};

