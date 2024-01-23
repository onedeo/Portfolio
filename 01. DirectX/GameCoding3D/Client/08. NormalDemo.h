#pragma once
#include "IExecute.h" // 하나의 실행 단위가 될것이다
#include "Geometry.h"

class NormalDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	shared_ptr<Shader> _shader;

	//Object
	//geometry + vertexbuffer + indexbuffer = Mesh
	shared_ptr<Geometry<VertexTextureNormalData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	Matrix _world = Matrix::Identity;

	//Camera
	shared_ptr<GameObject> _camera;

	shared_ptr<Texture> _texture;

	Vec3 _lightDir = Vec3(1.f, -1.f, 1.f);
};

