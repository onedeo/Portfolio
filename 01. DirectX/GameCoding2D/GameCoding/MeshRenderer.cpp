#include "pch.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Pipeline.h"
#include "Game.h"
#include "Mesh.h"

MeshRenderer::MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext) : Super(ComponentType::MeshRenderer), _device(device), _deviceContext(deviceContext)
{

	auto _texture1 = make_shared<Texture>(_device);
	_texture1->Create(L"Skeleton.png");

	//SetTexture(_texture1);
}

MeshRenderer::~MeshRenderer()
{
}

