#pragma once
#include "IExecute.h" // 하나의 실행 단위가 될것이다
#include "Geometry.h"

class QuadDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;


	shared_ptr<Shader> _shader;
	shared_ptr<Geometry<VertexColorData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
};

