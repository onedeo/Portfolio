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
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();

private:
	//�ﰢ�� �����
	void CreateGeometry();
	void CreateInputLayout();
	void CreateVS();
	void CreatePS();

	void CreateRasterizerState();
	void CreateSamplerState();
	void CreateBlendState();

	void CreateSRV(); //Shader Resource View

	void CreateConstantBuffer();

	void LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob);

private:
	HWND _hwnd;
	uint32 _width = 0;
	uint32 _height = 0;

private:
	//DX : ��ü���� Ʋ(�Լ�)�� ��������

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

private:
	// >> : �������� ���� �����
	vector<Vertex> _vertices;
	ComPtr<ID3D11Buffer> _vertexBuffer = nullptr;
	ComPtr<ID3D11InputLayout> _inputLayout = nullptr;
	/*
	[CPU<->RAM] : CPU ���� <-> [GPU<->VRAM] : GPU ����
	GPU���� ������ ������ �������� �Ѵ� :VertexBuffer
	*/
	
	// index buffer
	vector<uint32> _indices;
	ComPtr<ID3D11Buffer> _indexBuffer = nullptr;

	// VS
	ComPtr<ID3D11VertexShader> _vertexShader = nullptr;
	ComPtr<ID3DBlob> _vsBlob = nullptr;

	//  RS
	ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;

	// PS
	ComPtr<ID3D11PixelShader> _pixelShader = nullptr;
	ComPtr<ID3DBlob> _psBlob = nullptr;

	// SRV
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView = nullptr;
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView2 = nullptr;

	// Sampler State
	// �̹��� �� �� ������ ��� ó�� �� ������
	ComPtr<ID3D11SamplerState> _samplerState = nullptr;
	//BlendState
	ComPtr<ID3D11BlendState> _blendState = nullptr;

	// << : �������� ���� �����

private:
	TransformData _transformData;
	ComPtr<ID3D11Buffer> _constantBuffer;
};

