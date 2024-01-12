#pragma once
class Game
{
public:
	Game();
	~Game();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();

private:
	void RenderBegin();
	void RenderEnd();

private:
	HWND _hwnd;
	uint32 _width = 0;
	uint32 _height = 0;

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();

private: //���������� ���� �����
	void CreateGeometry();
	void CreateInputLayout();

	void CreateVS();
	void CreatePS();

	void LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob);

private:
	//DX : ��ü���� Ʋ(�Լ�)�� ��������

	// >> : device
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11DeviceContext> _deviceContext;
	/*
	- I : Interface�� ����ϴ� ��
	- Delete �ϴ� ���� �ƴ϶� Release�� �ؾ��Ѵ�
	AddRef ��� -> �ٸ� ������ ����ϸ� AddRef�� 1 �����ϰ�, Release�ϸ� 1 ����
	AddRef�� Release¦�� �ȸ�����? -> �޸� ���� -> �������� �ϴ� ���� �ٶ������� ����
	=> ������ �����ϴ� ���� �ƴϰ� ����Ʈ �����ͷ� ���� -> ComPtr<> ��� (wrl.h ����� ���� ���)
	- ���������̽� ������ �ϴ� ���ΰ�
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

	// >> : �������� ���� �����
	vector<Vertex> _vertices;
	ComPtr<ID3D11Buffer> _vertexBuffer = nullptr;
	ComPtr<ID3D11InputLayout> _inputLayout = nullptr;
	/*
	[CPU<->RAM] : CPU ���� <-> [GPU<->VRAM] : GPU ����
	GPU���� ������ ������ �������� �Ѵ� : Vertex Buffer
	*/

	// VS
	ComPtr<ID3D11VertexShader> _vertexShader = nullptr;
	ComPtr<ID3DBlob>  _vsBlob = nullptr;

	// PS
	ComPtr<ID3D11PixelShader> _pixelShader = nullptr;
	ComPtr<ID3DBlob> _psBlob = nullptr;

	// <<
};

