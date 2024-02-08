#include "pch.h"
#include "Scene.h"

void Scene::Start()
{
	unordered_set<shared_ptr<GameObject>> objects = _objects;
	for (shared_ptr<GameObject> obj : objects)
		obj->Start();
}

void Scene::Update()
{
	unordered_set<shared_ptr<GameObject>> objects = _objects;
	for (shared_ptr<GameObject> obj : objects)
		obj->Update();

	// Instancing
	vector<shared_ptr<GameObject>> temp;
	temp.insert(temp.end(), objects.begin(), objects.end());
	INSTANCING->Render(temp);
}

void Scene::LateUpdate()
{
	unordered_set<shared_ptr<GameObject>> objects = _objects;
	for (shared_ptr<GameObject> obj : objects)
		obj->LateUpdate();
}

void Scene::Add(shared_ptr<GameObject> object)
{
	_objects.insert(object);

	if (object->GetCamera() != nullptr)
		_cameras.insert(object);

	if (object->GetLight() != nullptr)
		_lights.insert(object);

}

void Scene::Remove(shared_ptr<GameObject> object)
{
	_objects.erase(object);
	_cameras.erase(object);
	_lights.erase(object);
}
