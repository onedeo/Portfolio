#pragma once

enum ShaderScope //리소스 사용 용도 지칭
{
	SS_NONE = 0,
	SS_VertexShader = (1 << 0), //비트 플래그를 사용 : 
	SS_PixelShader = (1 << 1),
	SS_Both = SS_VertexShader | SS_PixelShader //-> 로 하면 1 1 이 되기 때문에 위 2개 다 포함된다고 볼 수 있다.

};

class Shader
{
public:
	Shader(ComPtr<ID3D11Device> device);
	virtual ~Shader();

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

class VertexShader : public Shader
{ // 정점에 대한 변환 처리 (좌표, 속성(텍스처 좌표, 벡터 등)) 수치적인거
	using Super = Shader;
public:
	VertexShader(ComPtr<ID3D11Device> device);
	~VertexShader();

	virtual void Create(const wstring& path, const string& name, const string& version) override;

	ComPtr<ID3D11VertexShader> GetComPtr() { return _vertexShader; }

protected:
	ComPtr<ID3D11VertexShader> _vertexShader;
};


class PixelShader : public Shader
{ // vertex shader에서 처리된것의 최종 색상 계산 (텍스처 매핑, 빛 계산, 그림자 등 계산)
	using Super = Shader;
public:
	PixelShader(ComPtr<ID3D11Device> device);
	~PixelShader();

	virtual void Create(const wstring& path, const string& name, const string& version) override;

	ComPtr<ID3D11PixelShader> GetComPtr() { return _pixelShader; }

protected:
	ComPtr<ID3D11PixelShader> _pixelShader;
};