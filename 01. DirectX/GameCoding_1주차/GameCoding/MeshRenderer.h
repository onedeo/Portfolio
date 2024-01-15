#pragma once
class MeshRenderer : public Component
{
	using Super = Component;

public:

	MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	virtual ~MeshRenderer();

	virtual void Update() override;
	void Render(shared_ptr<Pipeline> pipeline);

private:
	// >> : 기하학적 도형 만들기
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11DeviceContext> _deviceContext;

	// Mesh 모형을 나타내는 그룹
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

	// Material
	shared_ptr<InputLayout> _inputLayout;
	shared_ptr<VertexShader> _vertexShader;
	shared_ptr<RasterizerState> _rasterizerState;
	shared_ptr<PixelShader> _pixelShader = nullptr;
	shared_ptr<Texture> _texture1;

	//Pipeline 상태와 관련
	shared_ptr<SamplerState> _samplerState;
	shared_ptr<BlendState> _blendState;

private:
	// Camera
	CameraData _cameraData;
	shared_ptr<ConstantBuffer<CameraData>> _cameraBuffer;

	// SRT
	TransformData _transformData;
	shared_ptr<ConstantBuffer<TransformData>> _transformBuffer;

	shared_ptr<Transform> _transform = make_shared<Transform>();
	shared_ptr<Transform> _parent = make_shared<Transform>();
};

