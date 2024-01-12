#pragma once
class RasterizerState
{ // 정점 데이터 화면 좌표로 변환, 그리기 영역 결정
public:
	RasterizerState(ComPtr<ID3D11Device> device);
	~RasterizerState();

	ComPtr<ID3D11RasterizerState> GetComPtr() { return _rasterizerState; }

	void Create();

private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11RasterizerState> _rasterizerState;
};

