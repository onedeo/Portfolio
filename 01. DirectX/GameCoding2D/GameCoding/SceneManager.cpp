#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Mesh.h"
#include "Animator.h"
#include "TestScene.h"

#include "CameraMove.h"

SceneManager::SceneManager(shared_ptr<Graphics> graphics)
{
	AddScene(make_shared<TestScene>(graphics), SceneName::Test);
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	if (_activeScene == nullptr) return;

	_activeScene->Awake();
	_activeScene->Start();
}

void SceneManager::Update()
{
	if (_activeScene == nullptr) return;

	_activeScene->Update();
	_activeScene->LateUpdate();
	_activeScene->FixedUpdate();
}

void SceneManager::AddScene(shared_ptr<Scene> scene, SceneName name)
{
	_scenes[name]=scene;
}

void SceneManager::LoadScene(SceneName sceneName)
{
	//Resource

	_activeScene = _scenes[sceneName];
	Init();
}

shared_ptr<Scene> SceneManager::LoadTestScene()
{
	//shared_ptr<Scene> scene = make_shared<Scene>();
	//
	////Camera
	//shared_ptr <GameObject>_camera = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	//{
	//	_camera->GetOrAddTransform();
	//	_camera->AddComponent(make_shared<Camera>());
	//	scene->AddGameObject(_camera);
	//}
	//{
	//	_camera->AddComponent(make_shared<CameraMove>());
	//}

	//Monster
	//{
	//	shared_ptr<GameObject> monster = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	//	monster->GetOrAddTransform()->SetPosition(Vec3{ 1,1,0 });
	//	{
	//		monster->GetOrAddTransform();
	//		auto meshRenderer = make_shared<MeshRenderer>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	//		monster->AddComponent(meshRenderer);

	//		auto material = RESOURCES->Get<Material>(L"Default");
	//		meshRenderer->setMaterial(material);

	//		auto mesh = RESOURCES->Get<Mesh>(L"Rectangle");
	//		meshRenderer->SetMesh(mesh);

	//	}
	//	{
	//		auto animator = make_shared<Animator>();
	//		monster->AddComponent(animator);
	//		auto anim = RESOURCES->Get<Animation>(L"SnakeAnim");
	//		animator->SetAnimation(anim);
	//	}
	//	scene->AddGameObject(monster);
	//}

	
		//Monster
	/*	shared_ptr<GameObject> monster = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
		{
			monster->GetOrAddTransform();
			auto meshRenderer = make_shared<MeshRenderer>(_graphics->GetDevice(), _graphics->GetDeviceContext());
			monster->AddComponent(meshRenderer);

			auto material = RESOURCES->Get<Material>(L"Default");
			meshRenderer->setMaterial(material);

			auto mesh = RESOURCES->Get<Mesh>(L"Rectangle");
			meshRenderer->SetMesh(mesh);

		}
		{
			auto animator = make_shared<Animator>();
			monster->AddComponent(animator);
			auto anim = RESOURCES->Get<Animation>(L"SnakeAnim");
			animator->SetAnimation(anim);
		}
		scene->AddGameObject(monster);
	}*/

	//return scene;
		return nullptr;
}
