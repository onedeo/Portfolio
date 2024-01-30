#pragma once

class Transform;
class GameObject;

enum class ComponentType : uint8
{
	// �Ѱ��� ���� �� ����
	Transform,
	MeshRenderer,
	ModelRenderer,
	Camera,
	Animator,

	// ������ ���� �� ����
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

	virtual void Awake() {} //�޸� ������ ����⸸ �ص� ����Ǵ°�
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