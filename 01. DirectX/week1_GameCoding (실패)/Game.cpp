#include "pch.h"
#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_width = GWinSizeX;
	_height = GWinSizeY;

	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	SetViewport();

	CreateGeometry();
	CreateVS();
	CreateInputLayout();
	CreatePS();
}

void Game::Update()
{
}

void Game::Render()
{
	// ���� �ܰ� : IA - VS - RS - PS - OM
	RenderBegin(); // �׸� �غ� (��ȭ�� �ʱ�ȭ ��)

	// >> �׸��� ����
	{
		uint32 stride = sizeof(Vertex);
		uint32 offset = 0;

		// IA
		_deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset);
		_deviceContext->IASetInputLayout(_inputLayout.Get());
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// VS
		_deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);

		// RS


		// PS
		_deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);

		// OM
		_deviceContext->Draw(_vertices.size(), 0);
	}


	RenderEnd(); //�׸� ��
}

void Game::RenderBegin()
{
	// >> : ���� �� �ʱ�ȭ
	_deviceContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), nullptr); // OM : OutputMerger (������ �ܰ�)
	_deviceContext->ClearRenderTargetView(_renderTargetView.Get(), _clearColor);
	_deviceContext->RSSetViewports(1, &_viewport);
}

void Game::RenderEnd()
{
	HRESULT hr = _swapChain->Present(1, 0); // [�߿�] �ϼ��� �� ���۸� ���� ���۷� ���
	CHECK(hr);
}

void Game::CreateDeviceAndSwapChain()
{
	// >> : ����ü�� (���� ���۸� ����)
	DXGI_SWAP_CHAIN_DESC desc; //�����(����ü��)�� ��� ���� ����
	ZeroMemory(&desc, sizeof(desc)); //memeset�� ������ ��� (0���� �ʱ�ȭ)
	{
		desc.BufferDesc.Width = _width;
		desc.BufferDesc.Height = _height;
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0; //��Ƽ ���ø��� ���� : �ȼ��� �ڿ������� ���Ҷ� (�缱�� ������� ��) ��� �Ұ���
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //���� ��� �뵵
		desc.BufferCount = 1; // ���� ��� ����
		desc.OutputWindow = _hwnd; // ������ �ڵ�
		desc.Windowed = true;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}
	// << :

	HRESULT hr = ::D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE, //�׷��� ī�带 ���, ������� �ϴ°ſ� ���� ���� (CPU�� ���� ����Ұ���)
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&desc,
		_swapChain.GetAddressOf(),// _device����Ʈ �����Ͷ� ��ü�� �������� .Get(), �ּҸ� �������� GetAddressOf()���
		_device.GetAddressOf(),
		nullptr,
		_deviceContext.GetAddressOf()
	);

	CHECK(hr); //���� ���� (define ����, assert ���)
	
}

void Game::CreateRenderTargetView()
{
	// >> : �ĸ� ���۸��� �׷��޶�� �Ÿ� �����ϴ� �Լ�
	HRESULT hr;

	ComPtr<ID3D11Texture2D> backBuffer = nullptr; //Texture : PNG ���� �����Ŷ�� ����
	hr = _swapChain->GetBuffer(0, _uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
	CHECK(hr);

	_device->CreateRenderTargetView(backBuffer.Get(), nullptr, _renderTargetView.GetAddressOf());
	CHECK(hr);

	//�ĸ� ���۸� backBuffer�� �־��ְ� _renderTargetView�� �־��� ����(?)

}

void Game::SetViewport()
{
	_viewport.TopLeftX = 0.0f;
	_viewport.TopLeftY = 0.0f;
	_viewport.Width = static_cast<float>(_width);
	_viewport.Height = static_cast<float>(_height);
	_viewport.MinDepth = 0.0f;
	_viewport.MaxDepth = 1.0f;
}

void Game::CreateGeometry()
{
	{ 
		//vertex ���� ����
		_vertices.resize(3);

		_vertices[0].position = Vec3(-0.5f, -0.5f, 0.0f);
		_vertices[0].color = Color(1.0f, 0.0f, 0.0f, 1.0f);
		_vertices[1].position = Vec3(0.0f, 0.5f, 0.0f);
		_vertices[1].color = Color(0.0f, 1.0f, 0.0f, 1.0f);
		_vertices[2].position = Vec3(0.5f, -0.5, 0.0f);
		_vertices[2].color = Color(0.0f, 0.0f, 1.0f, 1.0f);
	}

	{
		//VertexBuffer
		D3D11_BUFFER_DESC desc; // ���� ���� : GPU ���ۿ� ������ �� �ֵ��� ����
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE; //GPU�� ReadOnly�����ͷ� �ȴٴ� ��. �ٸ� �͵鵵 ã�ƺ���
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = (uint32)(sizeof(Vertex) * _vertices.size());

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = _vertices.data(); // ù��° �������� ���� �ּ� = &_vertices

		_device->CreateBuffer(&desc, &data, _vertexBuffer.GetAddressOf());
	}

}


void Game::CreateInputLayout()
{
	// GPU�� ������ ��� ���� ������ ���� ���ֱ�

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0, D3D11_INPUT_PER_VERTEX_DATA,0},
		{"COLOR",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12, D3D11_INPUT_PER_VERTEX_DATA,0}, //12 : ù ��°���� ���� 12��° ���ķ� COLOR�� ���۵ȴٴ� �ǹ�(POSITION�� R32,G32,B32�� �� 4����Ʈ�� 12����Ʈ�� ���Ŀ� �÷��� ���۵ȴٰ� �����
	};

	const int32 count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC);
	_device->CreateInputLayout(layout, count, _vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), _inputLayout.GetAddressOf());
}

void Game::CreateVS()
{
	LoadShaderFromFile(L"Default.hlsl", "main", "vs_5_0", _vsBlob);
	HRESULT hr = _device->CreateVertexShader(_vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), nullptr, _vertexShader.GetAddressOf());

	CHECK(hr);

}

void Game::CreatePS()
{
	LoadShaderFromFile(L"Default.hlsl", "PS", "ps_5_0", _psBlob);
	HRESULT hr = _device->CreatePixelShader(_psBlob->GetBufferPointer(), _psBlob->GetBufferSize(), nullptr, _pixelShader.GetAddressOf());

	CHECK(hr);
}

void Game::LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob)
{
	const uint32 compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

	HRESULT hr = ::D3DCompileFromFile(
		path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		name.c_str(),
		version.c_str(),
		compileFlag,
		0,
		blob.GetAddressOf(),
		nullptr);

	CHECK(hr);
}
