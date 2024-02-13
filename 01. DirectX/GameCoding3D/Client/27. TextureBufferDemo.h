#pragma once
class TextureBufferDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

private:
	ComPtr<ID3D11ShaderResourceView> MakeComputeShaderTexture();

private:
	shared_ptr<Shader> _shader;

};

