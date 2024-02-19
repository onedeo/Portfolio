#include "pch.h"
#include "29. ViewportDemo.h"
#include "Camera.h"
#include "CameraScript.h"
#include "Material.h"
#include "Model.h"
#include "ModelRenderer.h"
#include "ModelAnimator.h"
#include "Light.h"
#include "TextureBuffer.h"
#include "Viewport.h"

void ViewportDemo::Init()
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

	// Mesh
	{
		shared_ptr<Material> material = make_shared<Material>();
		material->SetShader(_shader);

		auto texture = RESOURCES->Load<Texture>(L"Echo", L"..\\Resources\\Textures\\echo.jpg");
		material->SetDiffuseMap(texture);

		MaterialDesc& desc = material->GetMaterialDesc();
		desc.ambient = Vec4(1.f);
		desc.diffuse = Vec4(1.f);
		desc.specular = Vec4(1.f);
		RESOURCES->Add(L"Veigar", material);
	}

	for (int32 i = 0; i < 500; i++)
	{
		auto obj = make_shared<GameObject>();
		obj->GetOrAddTransform()->SetPosition(Vec3(0.f));
		obj->AddComponent(make_shared<MeshRenderer>());
		{
			obj->GetMeshRenderer()->SetMaterial(RESOURCES->Get<Material>(L"Veigar"));
		}
		{
			auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
			obj->GetMeshRenderer()->SetMesh(mesh);
			obj->GetMeshRenderer()->SetPass(0);
		}

		CUR_SCENE->Add(obj);
	}

	////
}

void ViewportDemo::Update()
{
	static float width = 800.f;
	static float height = 600.f;
	static float x = 0.f;
	static float y = 0.f;

	ImGui::InputFloat("Width", &width, 10.f);
	ImGui::InputFloat("Height", &height, 10.f);
	ImGui::InputFloat("X", &x, 10.f);
	ImGui::InputFloat("Y", &y, 10.f);

	GRAPHICS->SetViewport(width, height, x, y);

	static Vec3 pos = Vec3(2, 0, 0);
	ImGui::InputFloat3("Pos", (float*)&pos);

	Viewport& vp = GRAPHICS->GetViewport();
	Vec3 pos2D = vp.Project(pos, Matrix::Identity, Camera::S_MatView, Camera::S_MatProjection);

	ImGui::InputFloat3("Pos2D", (float*)&pos2D);
	{
		Vec3 temp = vp.Unproject(pos2D, Matrix::Identity, Camera::S_MatView, Camera::S_MatProjection);
		ImGui::InputFloat3("Recalc", (float*)&temp);
	}
}

void ViewportDemo::Render()
{
}

ComPtr<ID3D11ShaderResourceView> ViewportDemo::MakeComputeShaderTexture()
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
