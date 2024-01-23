#pragma once
#include "IExecute.h" // �ϳ��� ���� ������ �ɰ��̴�
#include "Geometry.h"

class GlobalTestDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	shared_ptr<Shader> _shader;
	//Object
	//geometry + vertexbuffer + indexbuffer = Mesh
	shared_ptr<GameObject> _obj;
	//Camera
	shared_ptr<GameObject> _camera;
};

