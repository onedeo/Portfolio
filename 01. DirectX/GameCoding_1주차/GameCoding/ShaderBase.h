#pragma once

enum ShaderScope //���ҽ� ��� �뵵 ��Ī
{
	SS_NONE = 0,
	SS_VertexShader = (1 << 0), //��Ʈ �÷��׸� ��� : 
	SS_PixelShader = (1 << 1),
	SS_Both = SS_VertexShader | SS_PixelShader //-> �� �ϸ� 1 1 �� �Ǳ� ������ �� 2�� �� ���Եȴٰ� �� �� �ִ�.

};

class ShaderBase
{
public:
	ShaderBase(ComPtr<ID3D11Device> device);
	virtual ~ShaderBase();

	virtual void Create(const wstring& path, const string& name, const string& version) abstract;

	ComPtr<ID3DBlob> GetBlob() { return _blob; }

protected:
	void LoadShaderFromFile(const wstring& path, const string& name, const string& version);

protected:
	wstring _path;
	string _name;
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3DBlob> _blob;
};

class VertexShader : public ShaderBase
{ // ������ ���� ��ȯ ó�� (��ǥ, �Ӽ�(�ؽ�ó ��ǥ, ���� ��)) ��ġ���ΰ�
	using Super = ShaderBase;
public:
	VertexShader(ComPtr<ID3D11Device> device);
	~VertexShader();

	virtual void Create(const wstring& path, const string& name, const string& version) override;

	ComPtr<ID3D11VertexShader> GetComPtr() { return _vertexShader; }

protected:
	ComPtr<ID3D11VertexShader> _vertexShader;
};


class PixelShader : public ShaderBase
{ // vertex shader���� ó���Ȱ��� ���� ���� ��� (�ؽ�ó ����, �� ���, �׸��� �� ���)
	using Super = ShaderBase;
public:
	PixelShader(ComPtr<ID3D11Device> device);
	~PixelShader();

	virtual void Create(const wstring& path, const string& name, const string& version) override;

	ComPtr<ID3D11PixelShader> GetComPtr() { return _pixelShader; }

protected:
	ComPtr<ID3D11PixelShader> _pixelShader;
};