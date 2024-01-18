#pragma once
#include "Component.h"

class Transform : public Component
{ //계층구조도 관리한다
	using Super = Component;
public:
	Transform();
	~Transform();

	virtual void Awake() override;
	virtual void Update() override;

	void UpdateTransform();

	//Local
	Vec3 GetLocalScale() { return _localScale; }
	Vec3 GetLocalRotation() { return _localRotation; }
	Vec3 GetLocalPosition() { return _localPosition; }

	void SetLocalScale(Vec3 localScale) {_localScale = localScale; UpdateTransform();}
	void SetLocalRotation(Vec3 localRotation) { _localRotation = localRotation; UpdateTransform(); }
	void SetLocalPosition(Vec3 localPosition) { _localPosition = localPosition; UpdateTransform(); }

	// World
	Vec3 GetScale() { return _localScale; }
	Vec3 GetRotation() { return _localRotation; }
	Vec3 GetPosition() { return _localPosition; }
	Vec3 GetRight() { return _matWorld.Right(); }
	Vec3 GetUp() { return _matWorld.Up(); }
	Vec3 GetLook() { return _matWorld.Backward(); }

	void SetScale(const Vec3& worldScale);
	void SetRotation(const Vec3& worldRotation);
	void SetPosition(const Vec3& worldPosition);

	Matrix GetWorldMatrix() { return _matWorld; }

	//계층관계
	bool HasParent() { return false; }
	shared_ptr<Transform> GetParent() { return _parent; }
	void SetParent(shared_ptr<Transform> parent) { _parent = parent; }

	const vector<shared_ptr<Transform>>& GetChilderens() { return _children; }
	void SetChildren(vector<shared_ptr<Transform>> children) { _children = children; }
	void AddChildren(shared_ptr<Transform> child) { _children.push_back(child); }

private:
	// Local
	Vec3 _localPosition = SimpleMath::Vector3::Zero;
	Vec3 _localRotation = SimpleMath::Vector3::Zero;
	Vec3 _localScale = SimpleMath::Vector3::One;

	// Cache
	Matrix _matLocal = Matrix::Identity; //부모 좌표를 기준으로 변환 행렬
	Matrix _matWorld = Matrix::Identity;

	// World
	Vec3 _scale;
	Vec3 _rotation;	// x y z + w : 짐벌럭 현상 방지 위해 쿼터니언으로 회전 생성
	Vec3 _position;

private:
	shared_ptr<Transform> _parent;
	vector<shared_ptr<Transform>> _children;
};

