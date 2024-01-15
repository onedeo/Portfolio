#include "pch.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Pipeline.h"
#include "Game.h"

MeshRenderer::MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext) : Super(ComponentType::MeshRenderer), _device(device), _deviceContext(deviceContext)
{
	//�������� ���� ǥ��
	_geometry = make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateRectangle(_geometry);

	//������ gpu�� ���� ���� ��û, gpu�� ��� �ֵ���
	_vertexBuffer = make_shared<VertexBuffer>(_device);
	_vertexBuffer->Create(_geometry->GetVertices());

	_indexBuffer = make_shared<IndexBuffer>(_device);
	_indexBuffer->Create(_geometry->GetIndices());

	_vertexShader = make_shared<VertexShader>(_device);
	_vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");

	//������ gpu�� shader�� ��� ������� �˷��ִ°�
	_inputLayout = make_shared<InputLayout>(_device);
	_inputLayout->Create(VertexTextureData::descs, _vertexShader->GetBlob());

	_pixelShader = make_shared<PixelShader>(_device);
	_pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

	_rasterizerState = make_shared<RasterizerState>(_device);
	_rasterizerState->Create();

	_blendState = make_shared<BlendState>(_device);
	_blendState->Create();

	_cameraBuffer = make_shared<ConstantBuffer<CameraData>>(_device, _deviceContext);
	_cameraBuffer->Create();

	_transformBuffer = make_shared<ConstantBuffer<TransformData>>(_device, _deviceContext);
	_transformBuffer->Create();

	_texture1 = make_shared<Texture>(_device);
	_texture1->Create(L"Skeleton.png");

	_samplerState = make_shared<SamplerState>(_device);
	_samplerState->Create();
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Update()
{
	_cameraData.matView = Camera::S_MatView;
	_cameraData.matProjection = Camera::S_MatProjection;
	_cameraBuffer->CopyData(_cameraData);

	_transformData.matWorld = GetTransform()->GetWorldMatrix();
	_transformBuffer->CopyData(_transformData);

	//Render
	Render(GGame->GetPipeline());
}

void MeshRenderer::Render(shared_ptr<Pipeline> pipeline)
{
	// ��ü���� info�� ��� ���� render�ȿ��� info�� �������ִ� ���� �ƴϴ�.
	PipelineInfo info;
	info.inputLayout = _inputLayout;
	info.vertexShader = _vertexShader;
	info.pixelShader = _pixelShader;
	info.rasterizerState = _rasterizerState;
	info.blendState = _blendState;

	pipeline->UpdatePipeline(info);

	pipeline->SetVertexBuffer(_vertexBuffer);
	pipeline->SetIndexBuffer(_indexBuffer);

	pipeline->SetConstantBuffer(0, SS_VertexShader, _cameraBuffer); //CameraBuffer
	pipeline->SetConstantBuffer(1, SS_VertexShader, _transformBuffer); //transform buffer

	pipeline->SetTexture(0, SS_PixelShader, _texture1);
	pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);

	pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);
}
