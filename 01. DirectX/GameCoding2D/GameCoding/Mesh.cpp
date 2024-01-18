#include "pch.h"
#include "Mesh.h"

Mesh::Mesh(ComPtr<ID3D11Device> device) : Super(ResourceType::Mesh), _device(device)
{
}

Mesh::~Mesh()
{
}

void Mesh::CreateDefaultRectangle()
{
	//기하학적 도형 표현
	_geometry = make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateRectangle(_geometry);

	//도형을 gpu에 버퍼 생성 요청, gpu도 들고 있도록
	_vertexBuffer = make_shared<VertexBuffer>(_device);
	_vertexBuffer->Create(_geometry->GetVertices());

	_indexBuffer = make_shared<IndexBuffer>(_device);
	_indexBuffer->Create(_geometry->GetIndices());
}
