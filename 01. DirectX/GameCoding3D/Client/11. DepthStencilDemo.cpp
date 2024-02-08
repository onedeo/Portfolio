#include "pch.h"
#include "11. DepthStencilDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "GameObject.h"
#include "CameraScript.h"
#include "MeshRenderer.h"
#include "Turning.h"

void DepthStencilDemo::Init()
{
	_shader = make_shared<Shader>(L"08. GlobalTest.fx");
		
	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());
	_camera->GetTransform()->SetPosition(Vec3(0, 0, -3));

	//Object
	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform();
	_obj->AddComponent(make_shared<MeshRenderer>());
	{
		//_obj->GetMeshRenderer()->SetShader(_shader);
	}
	{
		RESOURCES->Init();
		auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_obj->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto texture = RESOURCES->Load<Texture>(L"echo", L"..\\Resources\\Textures\\echo.jpg");
		//_obj->GetMeshRenderer()->SetTexture(texture);
	}
	{
		_obj->AddComponent(make_shared<Turning>());
	}
	// Object2
	_obj2 = make_shared<GameObject>();
	_obj2->GetOrAddTransform()->SetPosition(Vec3{ 0.5f, 0.f, 2.f });
	_obj2->AddComponent(make_shared<MeshRenderer>());
	{
		//_obj2->GetMeshRenderer()->SetShader(_shader);
	}
	{
		auto mesh = RESOURCES->Get<Mesh>(L"Cube");
		_obj2->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto texture = RESOURCES->Load<Texture>(L"echo", L"..\\Resources\\Textures\\echo.jpg");
		//_obj2->GetMeshRenderer()->SetTexture(texture);
	}
	RENDER->Init(_shader);
}

void DepthStencilDemo::Update()
{
	_camera->Update();

	RENDER->Update();
	
	//DepthStencil이 없으면 그리는 순서대로 앞/뒤가 결정된다 (2d같이)
	_obj->Update();
	_obj2->Update();
}

void DepthStencilDemo::Render()
{

}
