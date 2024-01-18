#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "Animation.h"

ResourceManager::ResourceManager(ComPtr<ID3D11Device> device) : _device(device)
{
}

void ResourceManager::Init()
{
	CreateDefaultTexture();
	CreateDefaultMesh();
	CreateDefaultShader();
	CreateDefaultMaterial();
	CreateDefaultAnimation();
}

void ResourceManager::CreateDefaultTexture()
{
	{
		auto texture = make_shared<Texture>(_device);
		texture->SetName(L"Skeleton");
		texture->Create(L"Skeleton.png");
		Add(texture->GetName(), texture);
	}
	{
		auto texture = make_shared<Texture>(_device);
		texture->SetName(L"Snake");
		texture->Create(L"Snake.bmp");
		Add(texture->GetName(), texture);
	}
}

void ResourceManager::CreateDefaultMesh()
{
	//Mesh
	shared_ptr<Mesh> mesh = make_shared<Mesh>(_device);
	mesh->SetName(L"Rectangle");
	mesh->CreateDefaultRectangle();
	Add(mesh->GetName(), mesh);
}

void ResourceManager::CreateDefaultShader()
{
	auto vertexShader = make_shared<VertexShader>(_device);
	vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");

	//도형을 gpu랑 shader랑 어떻게 생겼는지 알려주는거
	auto inputLayout = make_shared<InputLayout>(_device);
	inputLayout->Create(VertexTextureData::descs, vertexShader->GetBlob());

	auto pixelShader = make_shared<PixelShader>(_device);
	pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

	//Shader
	shared_ptr<Shader> shader = make_shared<Shader>();
	shader->SetName(L"Default");
	shader->_vertexShader = vertexShader;
	shader->_inputLayout = inputLayout;
	shader->_pixelShader = pixelShader;
	Add(shader->GetName(), shader);

}

void ResourceManager::CreateDefaultMaterial()
{
	shared_ptr<Material> material = make_shared<Material>();
	material->SetName(L"Default");
	material->SetShader(Get<Shader>(L"Default"));
	material->SetTexture(Get<Texture>(L"Sekeleton"));
	Add(material->GetName(), material);
}

void ResourceManager::CreateDefaultAnimation()
{
	shared_ptr<Animation> animation = make_shared<Animation>();
	animation->SetName(L"SnakeAnim");
	animation->SetTexture(Get<Texture>(L"Snake"));
	animation->SetLoop(true);

	animation->AddKeyframe(Keyframe{ Vec2{0,0},Vec2{100.f, 100.f}, 0.1f });
	animation->AddKeyframe(Keyframe{ Vec2{100,0},Vec2{100.f, 100.f}, 0.1f });
	animation->AddKeyframe(Keyframe{ Vec2{200,0},Vec2{100.f, 100.f}, 0.1f });
	animation->AddKeyframe(Keyframe{ Vec2{300,0},Vec2{100.f, 100.f}, 0.1f });
	animation->AddKeyframe(Keyframe{ Vec2{400,0},Vec2{100.f, 100.f}, 0.1f });

	Add(animation->GetName(), animation);

	//XML + JSON
	/*
	JSON 장점 : XML 보다 가볍다. 파싱속도가 빠르다. 웹에서 활용한다
	XML 장점 : 계층구조에서 장점이 있다.(트리구조 처럼)
	*/
	animation->Save(L"TestAnim.xml");

	shared_ptr<Animation> anim2 = make_shared<Animation>();
	anim2->Load(L"TestAnim.xml");
	
	int a = 0;

}
