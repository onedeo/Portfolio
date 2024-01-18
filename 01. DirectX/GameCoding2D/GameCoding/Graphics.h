#pragma once
//���������� ȭ�鿡 �׸������ �ʿ��� ����

class Graphics
{
	DECLARE_SINGLE(Graphics);

public:
	Graphics(HWND hwnd);
	~Graphics();

	void RenderBegin();
	void RenderEnd();

	ComPtr<ID3D11Device> GetDevice() { return _device; }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() { return _deviceContext; }

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();


private:
	HWND _hwnd;
	uint32 _width = 0;
	uint32 _height = 0;

private:
	// >> : Device & SwapChain
	ComPtr<ID3D11Device> _device = nullptr;
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;
	/*
	-I : Interface�� ����ϴ� ��
		- Delete �ϴ� ���� �ƴ϶� Release�� �ؾ��Ѵ�
		AddRef ���->�ٸ� ������ ����ϸ� AddRef�� 1 �����ϰ�, Release�ϸ� 1 ����
		AddRef�� Release¦�� �ȸ����� ? ->�޸� ����->�������� �ϴ� ���� �ٶ������� ����
		= > ������ �����ϴ� ���� �ƴϰ� ����Ʈ �����ͷ� ����-> ComPtr<> ���(wrl.h ����� ���� ���)
		- �������̽� ������ �ϴ� ���ΰ�
			�پ��� GPU�� ������, ���� ����ȭ �ϴ� �԰����� ���̷�Ʈx���� ������ �͸� ������ �� �ִ� '�������̽�'

		- _device : ���ҽ� ����
		- _deviceContext : ���ҽ� ���
	*/
	ComPtr<IDXGISwapChain> _swapChain = nullptr;
	/*
	- ������۸� : �׸��°Ͱ� ȭ�鿡 ���̴� �Ͱ� ���ÿ� ����Ǹ� ���ܼ� ���̴°� �ذ�
		���� �����ӿ� ������ �ڼ��̴°� ����
	- ����ü�ε� ������۸��� ������ �������� ���� ����� �������� ����
	*/
	// << :

	// >> : Render Target View
	ComPtr<ID3D11RenderTargetView> _renderTargetView;
	// << :

	// >> : Misc
	D3D11_VIEWPORT _viewport = { 0 }; //ȭ���� ũ�⸦ �������ִ� �ڷ�
	float _clearColor[4] = { 0, 0, 0, 0 };
	// <<
};

