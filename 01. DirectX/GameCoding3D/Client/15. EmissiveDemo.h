#pragma once
#include "IExecute.h" // �ϳ��� ���� ������ �ɰ��̴�
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

