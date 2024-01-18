#pragma once
#include "IExecute.h" // 하나의 실행 단위가 될것이다

class TriangleDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	shared_ptr<Shader> _shader;
	vector<VertexData> _vertices;
	shared_ptr<VertexBuffer> _buffer;
};

