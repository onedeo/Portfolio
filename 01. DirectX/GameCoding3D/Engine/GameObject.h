#pragma once
#include "Component.h"

class MonoBehaviour;
class Transform;
class Camera;
class MeshRenderer;
class ModelRenderer;
//class Animator;

class GameObject : public enable_shared_from_this<GameObject>
{
public:
	GameObject();
	~GameObject();

	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FixedUpdate();

	shared_ptr<Component> GetFixedComponent(ComponentType type);
	shared_ptr<Transform> GetTransform();
	shared_ptr<Camera> GetCamera();
	shared_ptr<MeshRenderer> GetMeshRenderer();
	shared_ptr<ModelRenderer> GetModelRenderer();
	//shared_ptr<Animator> GetAnimator();

	shared_ptr<Transform> GetOrAddTransform();

	void AddComponent(shared_ptr<Component> component);

protected:
	std::array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components; //1개만 들어가는 것이기에 array로 크기를 지정
	vector<shared_ptr<MonoBehaviour>> _scripts;

};

