#pragma once
#include "IExecute.h" // 하나의 실행 단위가 될것이다
#include "Geometry.h"

class EmissiveDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	shared_ptr<Shader> _shader;
	//Object
	//geometry + vertexbuffer + indexbuffer = Mesh
	shared_ptr<GameObject> _obj;
	shared_ptr<GameObject> _obj2;
	//Camera
	shared_ptr<GameObject> _camera;
};

