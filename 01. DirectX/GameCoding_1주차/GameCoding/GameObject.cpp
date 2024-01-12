#include "pch.h"
#include "GameObject.h";

GameObject::GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext) : _device(device), _deviceContext(deviceContext)
{
	//기하학적 도형 표현
	_geometry = make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateRectangle(_geometry);

	//도형을 gpu에 버퍼 생성 요청, gpu도 들고 있도록
	_vertexBuffer = make_shared<VertexBuffer>(_device);
	_vertexBuffer->Create(_geometry->GetVertices());

	_indexBuffer = make_shared<IndexBuffer>(_device);
	_indexBuffer->Create(_geometry->GetIndices());

	_vertexShader = make_shared<VertexShader>(_device);
	_vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");

	//도형을 gpu랑 shader랑 어떻게 생겼는지 알려주는거
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
	_texture1->Create(L"turtle.png");

	_samplerState = make_shared<SamplerState>(_device);
	_samplerState->Create();

}

GameObject::~GameObject()
{
}

void GameObject::Awake()
{
	for (shared_ptr<Component>& component : _components)
	{
		if(component)
		component->Awake();
	}

	for (shared_ptr<Component>& script : _scripts)
	{
		script->Awake();
	}
}

void GameObject::Start()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
		component->Start();
	}

	for (shared_ptr<Component>& script : _scripts)
	{
		script->Start();
	}
}

void GameObject::Update()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
		component->Update();
	}

	for (shared_ptr<Component>& script : _scripts)
	{
		script->Update();
	}
	//TEMP
	if (GetCamera()) return;

	_cameraData.matView = Camera::S_MatView;
	//_cameraData.matView = Matrix::Identity;
	_cameraData.matProjection = Camera::S_MatProjection;
	//_cameraData.matProjection = Matrix::Identity;
	_cameraBuffer->CopyData(_cameraData);

	_transformData.matWorld = GetOrAddTransform()->GetWorldMatrix();
	_transformBuffer->CopyData(_transformData);
}

void GameObject::LateUpdate()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
		component->LateUpdate();
	}

	for (shared_ptr<Component>& script : _scripts)
	{
		script->LateUpdate();
	}
}

void GameObject::FixedUpdate()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
		component->FixedUpdate();
	}

	for (shared_ptr<Component>& script : _scripts)
	{
		script->FixedUpdate();
	}
}

shared_ptr<Component> GameObject::GetFixedComponent(ComponentType type)
{
	uint8 index = static_cast<uint8>(type);
	assert(index < FIXED_COMPONENT_COUNT);

	return _components[index];
}

shared_ptr<Transform> GameObject::GetTransform()
{
	shared_ptr<Component> component = GetFixedComponent(ComponentType::Transform);
	return static_pointer_cast<Transform>(component);
}

shared_ptr<Camera> GameObject::GetCamera()
{
	shared_ptr<Component> component = GetFixedComponent(ComponentType::Camera);
	return static_pointer_cast<Camera>(component);
}

shared_ptr<Transform> GameObject::GetOrAddTransform()
{
	if (GetTransform() == nullptr)
	{
		shared_ptr<Transform> transform = make_shared<Transform>();
		AddComponent(transform);
	}
	return GetTransform();
}

void GameObject::AddComponent(shared_ptr<Component> component)
{
	component->SetGameObject(shared_from_this());

	uint8 index = static_cast<uint8>(component->GetType());
	if (index < FIXED_COMPONENT_COUNT)
	{
		_components[index] = component;
	}
	else
	{
		_scripts.push_back(dynamic_pointer_cast<MonoBehaviour>(component));
	}
}

void GameObject::Render(shared_ptr<Pipeline> pipeline)
{
	// 물체마다 info를 들고 있지 render안에서 info를 설정해주는 것은 아니다.
	PipelineInfo info;
	info.inputLayout = _inputLayout;
	info.vertexShader = _vertexShader;
	info.pixelShader = _pixelShader;
	info.rasterizerState = _rasterizerState;
	info.blendState = _blendState;

	pipeline->UpdatePipeline(info);

	pipeline->SetVertexBuffer(_vertexBuffer);
	pipeline->SetIndexBuffer(_indexBuffer);

	pipeline->SetConstantBuffer(0, SS_VertexShader, _transformBuffer); //transform buffer
	pipeline->SetConstantBuffer(1, SS_VertexShader, _cameraBuffer); //CameraBuffer

	pipeline->SetTexture(0, SS_PixelShader, _texture1);
	pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);

	pipeline->DrawIndexed(_geometry->GetIndexCount(), 0, 0);
}
