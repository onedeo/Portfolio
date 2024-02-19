#include "pch.h"
#include "17. MaterialDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "GameObject.h"
#include "CameraScript.h"
#include "MeshRenderer.h"
#include "Turning.h"
#include "Material.h"

void MaterialDemo::Init()
{
	RESOURCES->Init();
	_shader = make_shared<Shader>(L"13. Lighting.fx");
		
	// Material
	{
		shared_ptr<Material> material = make_shared<Material>();
		{
			material->SetShader(_shader);
		}
		{
			auto texture = RESOURCES->Load<Texture>(L"echo", L"..\\Resources\\Textures\\echo.jpg");
			material->SetDiffuseMap(texture);
		}

		MaterialDesc& desc = material->GetMaterialDesc();
		desc.ambient = Vec4(1.f);
		desc.diffuse= Vec4(1.f);

		RESOURCES->Add(L"echo", material);
	}


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
		auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_obj->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto material = RESOURCES->Get<Material>(L"echo");
		_obj->GetMeshRenderer()->SetMaterial(material);
	}
	{
		_obj->AddComponent(make_shared<Turning>());
	}
	// Object2
	_obj2 = make_shared<GameObject>();
	_obj2->GetOrAddTransform()->SetPosition(Vec3{ 0.5f, 0.f, 2.f });
	_obj2->AddComponent(make_shared<MeshRenderer>());
	{
		auto mesh = RESOURCES->Get<Mesh>(L"Cube");
		_obj2->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		// Resource에서 가져오는 resource는 해당 리소스를 사용하는 모든 객체가 공유하는 하나의 리소스
		// 리소스의 어느 부분을 바꾸면 해당 리소스를 사용하는 모든 객체의 리소스 변경
		// 이를 위해 clone이란 함수 추가
		auto material = RESOURCES->Get<Material>(L"echo")->Clone();
		MaterialDesc& desc = material->GetMaterialDesc();
		desc.ambient = Vec4(0.f);
		desc.diffuse = Vec4(0.f);

		_obj2->GetMeshRenderer()->SetMaterial(material);
	}
	//
}

void MaterialDemo::Update()
{
	_camera->Update();
	//
	{
		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.5f);
		lightDesc.diffuse = Vec4(1.f);
		lightDesc.specular = Vec4(1.f, 1.f, 1.f, 1.f);
		lightDesc.direction = Vec3(0.f, -1.f, 0.f);
		//
	}

	{
		MaterialDesc desc;
		desc.ambient = Vec4(0.2f);
		desc.diffuse = Vec4(1.f);
		desc.specular = Vec4(1.f);
		//desc.emissive = Color(0.3f, 0.f, 0.f, 0.5f);

//
		_obj->Update();
	}

	{
		MaterialDesc desc;
		desc.ambient = Vec4(0.5f);
		desc.diffuse = Vec4(1.f);
		//desc.specular = Color(0.5f, 0.5f, 0.5f, 1.f);
		//desc.emissive = Color(1.f, 0.f, 0.f, 1.f);

//
		_obj2->Update();
	}
}

void MaterialDemo::Render()
{

}
