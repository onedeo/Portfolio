#pragma once
class BlendState
{	// 픽셀 색상 렌더링 시 현재의 픽셀 색상과 대상 색상을 어떻게 석을지 제어
	// 투명도와 같이 다양한 시각적 효과 제공
public:
	BlendState(ComPtr<ID3D11Device> device);
	~BlendState();

	void Create(D3D11_RENDER_TARGET_BLEND_DESC blendDesc =
		{
			true,
			D3D11_BLEND_SRC_ALPHA,
			D3D11_BLEND_INV_SRC_ALPHA,
			D3D11_BLEND_OP_ADD,
			D3D11_BLEND_ONE,
			D3D11_BLEND_ZERO,
			D3D11_BLEND_OP_ADD,
			D3D11_COLOR_WRITE_ENABLE_ALL,
		}, float factor = 0.0f);



	ComPtr<ID3D11BlendState> GetComPtr() { return _blendState; }
	const float* GetBlenderFactor() { return &_blendFactor; }
	uint32 GetSampleMask() { return _sampleMask; }


private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11BlendState> _blendState;
	float _blendFactor;
	uint32 _sampleMask = 0xFFFFFFFF;
};

