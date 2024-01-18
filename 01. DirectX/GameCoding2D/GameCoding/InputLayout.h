#pragma once
class InputLayout
{ // gpu�� ���� ���۸� ��� �о�������� ���� ����
public:
	InputLayout(ComPtr<ID3D11Device> device);
	~InputLayout();

	void Create(const vector<D3D11_INPUT_ELEMENT_DESC>& desc, ComPtr<ID3DBlob> blob);

	ComPtr<ID3D11InputLayout> GetComPtr() { return _inputLayout; }

private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11InputLayout> _inputLayout;
};

