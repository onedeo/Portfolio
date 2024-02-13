#include "pch.h"
#include "14. SpecularDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "GameObject.h"
#include "CameraScript.h"
#include "MeshRenderer.h"
#include "Turning.h"

void SpecularDemo::Init()
{
	RESOURCES->Init();
	_shader = make_shared<Shader>(L"11. Lighting_Specular.fx");
		
	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());
	_camera->GetTransform()->SetPosition(Vec3(0, 2, -3));
	_camera->GetTransform()->SetRotation(Vec3(0.4, 0, 0));

	//Object
	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform();
	_obj->AddComponent(make_shared<MeshRenderer>());
	{
		_obj->GetMeshRenderer()->SetShader(_shader);
	}
	{
		auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_obj->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto texture = RESOURCES->Load<Texture>(L"echo", L"..\\Resources\\Textures\\echo.jpg");
		_obj->GetMeshRenderer()->SetTexture(texture);
	}
	{
		_obj->AddComponent(make_shared<Turning>());
	}
	// Object2
	_obj2 = make_shared<GameObject>();
	_obj2->GetOrAddTransform()->SetPosition(Vec3{ 0.5f, 0.f, 2.f });
	_obj2->AddComponent(make_shared<MeshRenderer>());
	{
		_obj2->GetMeshRenderer()->SetShader(_shader);
	}
	{
		auto mesh = RESOURCES->Get<Mesh>(L"Cube");
		_obj2->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto texture = RESOURCES->Load<Texture>(L"echo", L"..\\Resources\\Textures\\echo.jpg");
		_obj2->GetMeshRenderer()->SetTexture(texture);
	}
	////
}

void SpecularDemo::Update()
{
	_camera->Update();
	////
	
	Vec4 light{ 1.f, 1.f, 1.f, 1.f };
	_shader->GetVector("LightSpecular")->SetFloatVector((float*)&light);

	//이건 빛의 위치가 아니라 벡터다. 이거를 eye의 뒤에 놓는다 해서 객체가 보이는 방향으로 빛이 향하는게 아니다
	Vec3 lightDir{ 1.f,0.f,0.f };
	lightDir.Normalize();
	_shader->GetVector("LightDir")->SetFloatVector((float*)&lightDir);

	{
		Vec4 materialAmbient(1.f);
		_shader->GetVector("MaterialSpecular")->SetFloatVector((float*)&light);
		_obj->Update();
	}
	{
		Vec4 materialAmbient(1.f);
		_shader->GetVector("MaterialSpecular")->SetFloatVector((float*)&light);
		_obj2->Update();
	}
}

void SpecularDemo::Render()
{

}
