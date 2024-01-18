#pragma once
#include "RenderHelper.h"

class RenderManager
{
	//그리는 물체들을 전용적으로 들고 있다
public:
	RenderManager(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	~RenderManager();

	void Init();
	void Update(shared_ptr<Graphics> graphics);

private:
	void PushCameraData();
	void PushTransformData();
	void PushAnimationData();

	void GatherRenderableObjects();
	void RenderObjects();

private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11DeviceContext> _deviceContext;
	shared_ptr<Pipeline> _pipeline;

private:
	vector<shared_ptr<GameObject>> _renderObjects;

private:
	// Camera
	CameraData _cameraData;
	shared_ptr<ConstantBuffer<CameraData>> _cameraBuffer;

	// SRT
	TransformData _transformData;
	shared_ptr<ConstantBuffer<TransformData>> _transformBuffer;

	//Animation
	AnimationData _animationData;
	shared_ptr<ConstantBuffer<AnimationData>> _animationBuffer;

private:
	//Pipeline 상태와 관련
	shared_ptr<RasterizerState> _rasterizerState;
	shared_ptr<SamplerState> _samplerState;
	shared_ptr<BlendState> _blendState;

	
};

