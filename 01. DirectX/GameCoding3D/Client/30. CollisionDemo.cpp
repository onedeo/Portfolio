#include "pch.h"
#include "30. CollisionDemo.h"
#include "Camera.h"
#include "CameraScript.h"
#include "Material.h"
#include "Model.h"
#include "ModelRenderer.h"
#include "ModelAnimator.h"
#include "Light.h"
#include "TextureBuffer.h"
#include "Viewport.h"
#include "SphereCollider.h"
#include "Scene.h"
#include "AABBBoxCollider.h"
#include "OBBBoxCollider.h"
#include "Terrain.h"

void CollisionDemo::Init()
{
	_shader = make_shared<Shader>(L"23. Render.fx");

	// Camera
	{
		auto camera = make_shared<GameObject>();
		camera->GetOrAddTransform()->SetPosition(Vec3{ 0.f, 0.f, -5.f });
		camera->AddComponent(make_shared<Camera>());
		camera->AddComponent(make_shared<CameraScript>());

		CUR_SCENE->Add(camera);
	}
	//Light
	{
		auto light = make_shared<GameObject>();
		light->AddComponent(make_shared<Light>());

		LightDesc lightDesc;
		lightDesc.ambient = Vec4(0.4f);
		lightDesc.diffuse = Vec4(1.f);
		lightDesc.specular = Vec4(0.1f);
		lightDesc.direction = Vec3(1.f, 0.f, 1.f);
		light->GetLight()->SetLightDesc(lightDesc);

		CUR_SCENE->Add(light);
	}

	// Material
	auto material = make_shared<Material>();
	material->SetShader(_shader);

	auto texture = RESOURCES->Load<Texture>(L"Echo", L"..\\Resources\\Textures\\echo.jpg");
	material->SetDiffuseMap(texture);

	MaterialDesc& desc = material->GetMaterialDesc();
	desc.ambient = Vec4(1.f);
	desc.diffuse = Vec4(1.f);
	desc.specular = Vec4(1.f);
	RESOURCES->Add(L"Echo", material);

	// Terrain
	{
		auto obj = make_shared<GameObject>();
		obj->AddComponent(make_shared<Terrain>());
		obj->GetTerrain()->Create(10, 10, RESOURCES->Get<Material>(L"Echo"));

		CUR_SCENE->Add(obj);
	}

	// Mesh
	{
		auto obj = make_shared<GameObject>();
		obj->GetOrAddTransform()->SetLocalPosition(Vec3(3.f, 0.f, 0.f));
		obj->AddComponent(make_shared<MeshRenderer>());
		{
			obj->GetMeshRenderer()->SetMaterial(RESOURCES->Get<Material>(L"Echo"));
		}
		{
			auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
			obj->GetMeshRenderer()->SetMesh(mesh);
			obj->GetMeshRenderer()->SetPass(0);
		}
		{
			auto collider = make_shared<SphereCollider>();
			collider->SetRadius(0.5f);
			obj->AddComponent(collider);
		}
		{
			obj->AddComponent(make_shared<MoveScript>());
		}
		CUR_SCENE->Add(obj);
	}

	// Mesh
	{
		auto obj = make_shared<GameObject>();
		obj->GetOrAddTransform()->SetLocalPosition(Vec3(0.f));
		obj->AddComponent(make_shared<MeshRenderer>());
		{
			obj->GetMeshRenderer()->SetMaterial(RESOURCES->Get<Material>(L"Echo"));
		}
		{
			auto mesh = RESOURCES->Get<Mesh>(L"Cube");
			obj->GetMeshRenderer()->SetMesh(mesh);
			obj->GetMeshRenderer()->SetPass(0);
		}
		/*
		{ // AABB
			auto collider = make_shared<AABBBoxCollider>();
			collider->GetBoundingBox().Extents = Vec3(0.5f);
			obj->AddComponent(collider);
		}
		*/
		{ // OBB
			obj->GetOrAddTransform()->SetRotation(Vec3(0, 45, 0));

			auto collider = make_shared<OBBBoxCollider>();
			collider->GetBoundingBox().Extents = Vec3(0.5f);
			collider->GetBoundingBox().Orientation = Quaternion::CreateFromYawPitchRoll(45, 0, 0);
			obj->AddComponent(collider);
		}

		CUR_SCENE->Add(obj);
	}
}

void CollisionDemo::Update()
{
	if (INPUT->GetButtonDown(KEY_TYPE::LBUTTON))
	{
		int32 mouseX = INPUT->GetMousePos().x;
		int32 mouseY = INPUT->GetMousePos().y;

		// Picking
		auto pickObj = CUR_SCENE->Pick(mouseX, mouseY);
		if (pickObj)
		{
			CUR_SCENE->Remove(pickObj);
		}
	}
}

void CollisionDemo::Render()
{
}

ComPtr<ID3D11ShaderResourceView> CollisionDemo::MakeComputeShaderTexture()
{
	auto shader = make_shared<Shader>(L"26. TextureBuffer.fx");

	auto texture = RESOURCES->Load<Texture>(L"Veigar", L"..\\Resources\\Textures\\veigar.jpg");
	shared_ptr<TextureBuffer> textureBuffer = make_shared<TextureBuffer>(texture->GetTexture2D());

	shader->GetSRV("Input")->SetResource(textureBuffer->GetSRV().Get());
	shader->GetUAV("Output")->SetUnorderedAccessView(textureBuffer->GetUAV().Get());

	uint32 width = textureBuffer->GetWidth();
	uint32 height = textureBuffer->GetHeight();
	uint32 arraySize = textureBuffer->GetArraySize();

	uint32 x = max(1, (width + 31) / 32);
	uint32 y = max(1, (height + 31) / 32);
	shader->Dispatch(0, 0, x, y, arraySize);

	return textureBuffer->GetOutputSRV();
}

void MoveScript::Update()
{
	auto pos = GetTransform()->GetPosition();
	pos.x -= DT * 1.0f;
	GetTransform()->SetPosition(pos);
}
