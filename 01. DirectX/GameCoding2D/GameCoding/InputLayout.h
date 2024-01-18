#pragma once
class InputLayout
{ // gpu가 정점 버퍼를 어떻에 읽어들일지에 대한 형식
public:
	InputLayout(ComPtr<ID3D11Device> device);
	~InputLayout();

	void Create(const vector<D3D11_INPUT_ELEMENT_DESC>& desc, ComPtr<ID3DBlob> blob);

	ComPtr<ID3D11InputLayout> GetComPtr() { return _inputLayout; }

private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11InputLayout> _inputLayout;
};

