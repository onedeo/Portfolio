#pragma once
#include "Component.h"

class MonoBehaviour;
class Transform;
class Camera;

class GameObject : public enable_shared_from_this<GameObject>
{
public:
	GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	~GameObject();

	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FixedUpdate();

	shared_ptr<Component> GetFixedComponent(ComponentType type);
	shared_ptr<Transform> GetTransform();
	shared_ptr<Camera> GetCamera();

	shared_ptr<Transform> GetOrAddTransform();

	void AddComponent(shared_ptr<Component> component);

	void Render(shared_ptr<Pipeline> pipeline);

private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11DeviceContext> _deviceContext;

	// >> : 기하학적 도형 만들기
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	shared_ptr<InputLayout> _inputLayout;
	// VS
	shared_ptr<VertexShader> _vertexShader;
	//  RS
	shared_ptr<RasterizerState> _rasterizerState;
	// PS
	shared_ptr<PixelShader> _pixelShader = nullptr;
	// SRV
	shared_ptr<Texture> _texture1;
	// Sampler State
	shared_ptr<SamplerState> _samplerState;
	//BlendState
	shared_ptr<BlendState> _blendState;

private:
	CameraData _cameraData;
	shared_ptr<ConstantBuffer<CameraData>> _cameraBuffer;

	TransformData _transformData;
	shared_ptr<ConstantBuffer<TransformData>> _transformBuffer;

	shared_ptr<Transform> _transform = make_shared<Transform>();
	shared_ptr<Transform> _parent = make_shared<Transform>();

protected:
	std::array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components; //1개만 들어가는 것이기에 array로 크기를 지정
	vector<shared_ptr<Component>> _scripts;

};

