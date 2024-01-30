#pragma once

class Transform;
class GameObject;

enum class ComponentType : uint8
{
	// 한개만 있을 수 있음
	Transform,
	MeshRenderer,
	ModelRenderer,
	Camera,
	Animator,

	// 여러개 있을 수 있음
	Script,

	End,
};
enum
{
	FIXED_COMPONENT_COUNT = static_cast<uint8>(ComponentType::End) - 1,
};

class Component
{
public:
	Component(ComponentType type);
	virtual ~Component();

	virtual void Awake() {} //메모리 상으로 만들기만 해도 실행되는거
	virtual void Start() {}

	virtual void Update() {}
	virtual void LateUpdate() {}
	virtual void FixedUpdate() {}

public:
	ComponentType GetType() { return _type; }

	shared_ptr<GameObject> GetGameObject();
	shared_ptr<Transform> GetTransform();


private:
	friend class GameObject;
	void SetGameObject(shared_ptr<GameObject> gameObject) { _gameObject = gameObject; }

protected:
	ComponentType _type;
	weak_ptr<GameObject> _gameObject;

};