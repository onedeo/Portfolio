#include "pch.h"
#include "TestScene.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Mesh.h"
#include "Animator.h"

#include "CameraMove.h"


TestScene::TestScene(shared_ptr<Graphics> graphics) : Scene(graphics)
{
}

TestScene::~TestScene()
{
}

void TestScene::Awake()
{
	AddSceneObjects();
	Scene::Awake();
}
void TestScene::AddSceneObjects()
{
	shared_ptr <GameObject>_camera = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	{
		_camera->GetOrAddTransform();
		_camera->AddComponent(make_shared<Camera>());
	}
	{
		_camera->AddComponent(make_shared<CameraMove>());
	}
		AddGameObject(_camera);

	shared_ptr<GameObject> monster = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	monster->GetOrAddTransform()->SetPosition(Vec3{ 1,1,0 });
	{
		monster->GetOrAddTransform();
		auto meshRenderer = make_shared<MeshRenderer>(_graphics->GetDevice(), _graphics->GetDeviceContext());
		monster->AddComponent(meshRenderer);

		auto material = RESOURCES->Get<Material>(L"Default");
		meshRenderer->SetMaterial(material);

		auto mesh = RESOURCES->Get<Mesh>(L"Rectangle");
		meshRenderer->SetMesh(mesh);

	}
	{
		auto animator = make_shared<Animator>();
		monster->AddComponent(animator);
		auto anim = RESOURCES->Get<Animation>(L"SnakeAnim");
		animator->SetAnimation(anim);
	}
	AddGameObject(monster);
}

