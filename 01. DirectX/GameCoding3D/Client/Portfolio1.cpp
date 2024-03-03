#include "pch.h"
#include "Portfolio1.h"
#include "Camera.h"
#include "CameraScript.h"
#include "Material.h"
#include "Model.h"
#include "ModelRenderer.h"
#include "ModelAnimator.h"
#include "Light.h"
#include "GeometryHelper.h"
#include "Turning.h"

void Portfolio1::Init()
{
	_shader = make_shared<Shader>(L"23. Render.fx");

	// Camera
	auto camera = make_shared<GameObject>();
	camera->GetOrAddTransform()->SetPosition(Vec3{ 0.f, 0.f, -5.f });
	camera->AddComponent(make_shared<Camera>());
	camera->AddComponent(make_shared<CameraScript>());

	//Light
	auto light = make_shared<GameObject>();
	light->AddComponent(make_shared<Light>());
	LightDesc lightDesc;
	lightDesc.ambient = Vec4(1.f);
	lightDesc.diffuse = Vec4(0.5f);
	lightDesc.specular = Vec4(0.5f);
	lightDesc.direction = Vec3(1.f, 1.f, 1.f);
	light->GetLight()->SetLightDesc(lightDesc);

	//Scenes
	for (int i = 0; i < END; i++)
	{
		_scenes[i] = make_shared<Scene>();
		_scenes[i]->Add(camera);
		_scenes[i]->Add(light);
	}

	LoadAll();

	SetSceneBasic();
	SetSceneLights();
	SetSceneHeight();

	SCENE->ChangeScene(_scenes[BASIC]);
}

void Portfolio1::Update()
{
	//SetGUI();
}

void Portfolio1::Render()
{

}

void Portfolio1::SetGUI()
{	
	ImGui::SetNextWindowSize(ImVec2(200, 400));
	if (ImGui::Begin("Test",NULL, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoMove))
	{

	}
	ImGui::End();

	
}

void Portfolio1::SetSceneBasic()
{
	// Sphere
	{
		auto obj = make_shared<GameObject>();
		obj->GetOrAddTransform()->SetPosition(Vec3(0.f,0.5f, 0.f));
		obj->AddComponent(make_shared<MeshRenderer>());
		obj->GetMeshRenderer()->SetMaterial(RESOURCES->Get<Material>(L"Veigar"));
		auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
		obj->GetMeshRenderer()->SetMesh(mesh);
		obj->SetName("Sphere");
		obj->AddComponent(make_shared<Turning>());

		_scenes[BASIC]->Add(obj);
	}
	
	// Cube
	{
		auto obj = make_shared<GameObject>();
		obj->GetOrAddTransform()->SetPosition(Vec3(2.f, 0.5f, 0.f));
		obj->AddComponent(make_shared<MeshRenderer>());
		obj->GetMeshRenderer()->SetMaterial(RESOURCES->Get<Material>(L"Echo"));
		auto mesh = RESOURCES->Get<Mesh>(L"Cube");
		obj->GetMeshRenderer()->SetMesh(mesh);
		obj->SetName("Cube");
		obj->AddComponent(make_shared<Turning>());

		_scenes[BASIC]->Add(obj);
	}

	// Normal Leather
	{
		auto obj = make_shared<GameObject>();
		obj->GetOrAddTransform()->SetPosition(Vec3(4.0f, 0.f, 0.f));
		obj->AddComponent(make_shared<MeshRenderer>());
		auto mesh = RESOURCES->Get<Mesh>(L"Cube");
		obj->GetMeshRenderer()->SetMesh(mesh);
		auto material = RESOURCES->Get<Material>(L"Leather");
		obj->GetMeshRenderer()->SetMaterial(material);
		obj->AddComponent(make_shared<Turning>());

		_scenes[BASIC]->Add(obj);
	}

	// Normal Circle
	{
		auto obj = make_shared<GameObject>();
		obj->GetOrAddTransform()->SetPosition(Vec3(6.f, 0.5f, 0.f));
		obj->AddComponent(make_shared<MeshRenderer>());
		obj->GetMeshRenderer()->SetMaterial(RESOURCES->Get<Material>(L"Circles"));
		auto mesh = RESOURCES->Get<Mesh>(L"Cube");
		obj->GetMeshRenderer()->SetMesh(mesh);
		obj->AddComponent(make_shared<Turning>());

		_scenes[BASIC]->Add(obj);
	}

	// Minecraft
	{	
		shared_ptr<GameObject> obj[6];
		for (int i = 0; i < 6; i++)
		{
			obj[i] = make_shared<GameObject>();
			obj[i]->AddComponent(make_shared<MeshRenderer>());
			obj[i]->GetMeshRenderer()->SetMaterial(RESOURCES->Get<Material>(L"Batman"));
		}
		for (int i = 1; i < 6; i++)
		{
			obj[0]->GetOrAddTransform()->AddChildren(obj[i]->GetOrAddTransform());
			obj[i]->GetOrAddTransform()->SetParent(obj[0]->GetOrAddTransform());
		}

		// Body
		obj[0]->GetOrAddTransform()->SetPosition(Vec3(-2.f, 1.f, 0.f));
		obj[0]->GetOrAddTransform()->SetScale(Vec3(0.4f, 0.6f, 0.2f));
		obj[0]->GetOrAddTransform()->SetLocalRotation(Vec3(0.f, XM_PI, 0.f));
		auto mesh = make_shared<Mesh>();
		obj[0]->GetMeshRenderer()->SetMesh(mesh);
		mesh->CreateBody();
		RESOURCES->Add(L"MCBody", mesh);
		obj[0]->SetName("MCBody");
		obj[0]->AddComponent(make_shared<Turning>());

		// Head
		obj[1]->GetOrAddTransform()->SetLocalPosition(Vec3(0.f, 0.85f, 0.f));
		obj[1]->GetOrAddTransform()->SetScale(Vec3(0.4f, 0.4f, 0.4f));
		auto mesh1 = make_shared<Mesh>();
		obj[1]->GetMeshRenderer()->SetMesh(mesh1);
		mesh1->CreateHead();
		RESOURCES->Add(L"MCHead", mesh1);
		obj[1]->SetName("MCHead");
				
		// LeftArm
		obj[2]->GetOrAddTransform()->SetLocalPosition(Vec3(-0.75f, 0.f, 0.f));
		obj[2]->GetOrAddTransform()->SetScale(Vec3(0.2f, 0.6f, 0.2f));
		auto mesh2 = make_shared<Mesh>();
		obj[2]->GetMeshRenderer()->SetMesh(mesh2);
		mesh2->CreateLArm();
		RESOURCES->Add(L"MCLArm", mesh2);
		obj[2]->SetName("MCLArm");

		// RightArm
		obj[3]->GetOrAddTransform()->SetLocalPosition(Vec3(0.75f, 0.f, 0.f));
		obj[3]->GetOrAddTransform()->SetScale(Vec3(0.2f, 0.6f, 0.2f));
		auto mesh3 = make_shared<Mesh>();
		obj[3]->GetMeshRenderer()->SetMesh(mesh3);
		mesh3->CreateRArm();
		RESOURCES->Add(L"MCRArm", mesh3);
		obj[3]->SetName("MCRArm");

		// LeftLeg
		obj[4]->GetOrAddTransform()->SetLocalPosition(Vec3(-0.25f, -1.f, 0.f));
		obj[4]->GetOrAddTransform()->SetScale(Vec3(0.2f, 0.6f, 0.2f));
		auto mesh4 = make_shared<Mesh>();
		obj[4]->GetMeshRenderer()->SetMesh(mesh4);
		mesh4->CreateRArm();
		RESOURCES->Add(L"MCRArm", mesh4);
		obj[4]->SetName("MCRArm");


		// RightLeg
		obj[5]->GetOrAddTransform()->SetLocalPosition(Vec3(0.25f, -1.f, 0.f));
		obj[5]->GetOrAddTransform()->SetScale(Vec3(0.2f, 0.6f, 0.2f));
		auto mesh5 = make_shared<Mesh>();
		obj[5]->GetMeshRenderer()->SetMesh(mesh5);
		mesh5->CreateRArm();
		RESOURCES->Add(L"MCRArm", mesh5);
		obj[5]->SetName("MCRArm");

		for (int i = 0; i < 6; i++)
			_scenes[BASIC]->Add(obj[i]);
	}

	// Ellie
	{
		auto m1 = make_shared<Model>();
		m1->ReadModel(L"Ellie/Ellie");
		m1->ReadMaterial(L"Ellie/Ellie");

		auto obj = make_shared<GameObject>();
		obj->GetOrAddTransform()->SetPosition(Vec3(-4.0f, 0.f, 0.f));
		obj->GetOrAddTransform()->SetScale(Vec3(0.01f));
		obj->AddComponent(make_shared<ModelRenderer>(_shader));
		obj->GetModelRenderer()->SetModel(m1);
		obj->AddComponent(make_shared<Turning>());

		_scenes[BASIC]->Add(obj);
	}

	// GRID
	{
		auto obj = make_shared<GameObject>();
		obj->GetOrAddTransform()->SetPosition(Vec3(-50,0,-50));
		obj->AddComponent(make_shared<MeshRenderer>());
		obj->GetMeshRenderer()->SetMaterial(RESOURCES->Get<Material>(L"Black"));
		auto mesh = make_shared<Mesh>();
		mesh->CreateGrid(100, 100);
		RESOURCES->Add(L"Grid", mesh);
		obj->GetMeshRenderer()->SetMesh(mesh);
		obj->GetMeshRenderer()->SetPass(3);

		_scenes[BASIC]->Add(obj);
	}
	
}

void Portfolio1::SetSceneLights()
{
}

void Portfolio1::SetSceneHeight()
{
}

void Portfolio1::LoadAll()
{
	LoadTextures();
}

void Portfolio1::LoadTextures()
{
	// Texture1 veigar
	{
		if (!RESOURCES->Exists<Texture>(L"Veigar"))
		{
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(_shader);
			auto texture = RESOURCES->Load<Texture>(L"Veigar", L"..\\Resources\\Textures\\veigar.jpg");
			material->SetDiffuseMap(texture);
			MaterialDesc& desc = material->GetMaterialDesc();
			desc.ambient = Vec4(1.f);
			desc.diffuse = Vec4(1.f);
			desc.specular = Vec4(1.f);
			RESOURCES->Add(L"Veigar", material);
		}
	}
	// Texture2 echo
	{
		if (!RESOURCES->Exists<Texture>(L"Echo"))
		{
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(_shader);
			auto texture = RESOURCES->Load<Texture>(L"Echo", L"..\\Resources\\Textures\\echo.jpg");
			material->SetDiffuseMap(texture);
			MaterialDesc& desc = material->GetMaterialDesc();
			desc.ambient = Vec4(1.f);
			desc.diffuse = Vec4(1.f);
			desc.specular = Vec4(1.f);
			RESOURCES->Add(L"Echo", material);
		}
	}
	// Texture black
	{
		if (!RESOURCES->Exists<Texture>(L"Black"))
		{
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(_shader);
			auto texture = RESOURCES->Load<Texture>(L"Black", L"..\\Resources\\Textures\\black.png");
			material->SetDiffuseMap(texture);
			MaterialDesc& desc = material->GetMaterialDesc();
			desc.ambient = Vec4(1.f);
			desc.diffuse = Vec4(1.f);
			desc.specular = Vec4(1.f);
			RESOURCES->Add(L"Black", material);
		}
	}
	// Texture Minecraft
	{
		if (!RESOURCES->Exists<Texture>(L"Batman"))
		{
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(_shader);
			auto texture = RESOURCES->Load<Texture>(L"Batman", L"..\\Resources\\Textures\\batman.png");
			material->SetDiffuseMap(texture);
			MaterialDesc& desc = material->GetMaterialDesc();
			desc.ambient = Vec4(1.f);
			desc.diffuse = Vec4(1.f);
			desc.specular = Vec4(1.f);
			RESOURCES->Add(L"Batman", material);
		}
	}
	// Texture Leather
	{
		if (!RESOURCES->Exists<Texture>(L"Leather"))
		{
			auto material = make_shared<Material>();
			material->SetShader(_shader);
			{
				auto diffuseTexture = RESOURCES->Load<Texture>(L"Leather", L"..\\Resources\\Textures\\Leather.jpg");
				material->SetDiffuseMap(diffuseTexture);
			}
			{
				auto normalTexture = RESOURCES->Load<Texture>(L"LeatherNormal", L"..\\Resources\\Textures\\Leather_Normal.jpg");
				material->SetNormalMap(normalTexture);
			}
			MaterialDesc& desc = material->GetMaterialDesc();
			desc.ambient = Vec4(1.f);
			desc.diffuse = Vec4(1.f);
			desc.specular = Vec4(1.f);
			RESOURCES->Add(L"Leather", material);
		}
	}
	// TextureCircles
	{
		if (!RESOURCES->Exists<Texture>(L"Circles"))
		{
			auto material = make_shared<Material>();
			material->SetShader(_shader);
			{
				auto diffuseTexture = RESOURCES->Load<Texture>(L"Circles", L"..\\Resources\\Textures\\Circles.png");
				material->SetDiffuseMap(diffuseTexture);
			}
			{
				auto normalTexture = RESOURCES->Load<Texture>(L"Circles_Normal", L"..\\Resources\\Textures\\Circles_Normal.png");
				material->SetNormalMap(normalTexture);
			}
			MaterialDesc& desc = material->GetMaterialDesc();
			desc.ambient = Vec4(1.f);
			desc.diffuse = Vec4(1.f);
			desc.specular = Vec4(1.f);
			RESOURCES->Add(L"Circles", material);
		}
	}
}

