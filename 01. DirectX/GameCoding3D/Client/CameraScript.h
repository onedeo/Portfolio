#pragma once
#include "MonoBehaviour.h"

class CameraScript : public MonoBehaviour
{
public:
	virtual void Start() override;
	virtual void Update() override;

private:
	Matrix FollowTarget(Vec3* target);
	void KeyboardInput();
	void MouseInput();

private:
	Vec3* _target = nullptr;
	float _speed = 10.0f;

	bool isLbuttonDown = false;
	Vec2 prevMouse;
	Vec3 camRotAngle;
};

