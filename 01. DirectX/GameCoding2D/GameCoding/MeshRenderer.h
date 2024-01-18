#pragma once
#include "Material.h"
#include "Shader.h"

class Mesh;
class Material;
class Shader;

class MeshRenderer : public Component
{
	using Super = Component;

public:
	MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	virtual ~MeshRenderer();

	void SetMaterial(shared_ptr<Material> material) { _material = material; }
	void SetShader(shared_ptr<Shader> shader) { _material->SetShader(shader); }
	void SetMesh(shared_ptr<Mesh> mesh) { _mesh = mesh; }
	void SetTexture(shared_ptr<Texture> texture) { _material->SetTexture(texture); }

	auto GetMaterial() { return _material; }
	auto GetVertexShader() { return GetMaterial()->GetShader()->GetVertexShader(); }
	auto GetInputLayout() { return GetMaterial()->GetShader()->GetInputLayout(); }
	auto GetPixelShader() { return GetMaterial()->GetShader()->GetPixelShader(); }
	
	shared_ptr<Mesh> GetMesh() { return _mesh; }
	auto GetTexture() { return GetMaterial()->GetTexture(); }



private:
	// >> : 기하학적 도형 만들기
	ComPtr<ID3D11Device> _device;

	friend class RenderManager;

	ComPtr<ID3D11DeviceContext> _deviceContext;

	//Mesh
	shared_ptr<Mesh> _mesh;
	shared_ptr<Material> _material;
};

