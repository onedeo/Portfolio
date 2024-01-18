#pragma once
class SamplerState
{	// texture을 입힐 때 빈곳을 어떻게 할것인지 : 빈곳을 빈곳으로 놔둘건지, 빈곳을 texutre 반복할건지, 거울로 할건지 등
	// min mag 설정 : 객체가 그려지는 영역보다 작게 표시될때 어떻게 할건지, 영역보다 커질 때 어떻게 할건지
public:
	SamplerState(ComPtr<ID3D11Device> device);
	~SamplerState();

	ComPtr<ID3D11SamplerState> GetComPtr() { return _samplerState; }

	void Create();

private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11SamplerState> _samplerState;
};

