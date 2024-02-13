#include "pch.h"
#include "12. AmbientDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "GameObject.h"
#include "CameraScript.h"
#include "MeshRenderer.h"
#include "Turning.h"

void AmbientDemo::Init()
{
	_shader = make_shared<Shader>(L"09. Lighting_Ambient.fx");
		
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
		RESOURCES->Init();
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

void AmbientDemo::Update()
{
	_camera->Update();

	////
	
	Vec4 lightAmbient{ 1.f, 0.5f, 0.2f, 1.f };
	_shader->GetVector("LightAmbient")->SetFloatVector((float*)&lightAmbient);
	{
		Vec4 materialAmbient(1.f);
		_shader->GetVector("MaterialAmbient")->SetFloatVector((float*)&materialAmbient);
		_obj->Update();
	}
	{
		Vec4 materialAmbient(1.f);
		_shader->GetVector("MaterialAmbient")->SetFloatVector((float*)&materialAmbient);
		_obj2->Update();
	}
}

void AmbientDemo::Render()
{

}
