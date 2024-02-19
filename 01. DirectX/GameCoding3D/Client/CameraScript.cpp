#include "pch.h"
#include "CameraScript.h"

void CameraScript::Start()
{
}

void CameraScript::Update()
{
	KeyboardInput();
	MouseInput();
}

Matrix CameraScript::FollowTarget(Vec3* target)
{
	_target = target;

	RECT rc;
	GetClientRect(GAME->GetGameDesc().hWnd, &rc);

	Matrix matProj = XMMatrixPerspectiveFovLH(XM_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.f);

	return matProj;
}

void CameraScript::KeyboardInput()
{
	float dt = TIME->GetDeltaTime();

	Vec3 pos = GetTransform()->GetPosition();

	if (INPUT->GetButton(KEY_TYPE::W))
		pos += GetTransform()->GetLook() * _speed * dt;

	if (INPUT->GetButton(KEY_TYPE::S))
		pos -= GetTransform()->GetLook() * _speed * dt;

	if (INPUT->GetButton(KEY_TYPE::A))
		pos -= GetTransform()->GetRight() * _speed * dt;

	if (INPUT->GetButton(KEY_TYPE::D))
		pos += GetTransform()->GetRight() * _speed * dt;
	
	if (INPUT->GetButton(KEY_TYPE::Q))
		pos -= GetTransform()->GetUp() * _speed * dt;
	
	if (INPUT->GetButton(KEY_TYPE::E))
		pos += GetTransform()->GetUp() * _speed * dt;
	
	GetTransform()->SetPosition(pos);
}

void CameraScript::MouseInput()
{
	if (INPUT->GetButtonDown(KEY_TYPE::RBUTTON))
	{
		prevMouse.x = INPUT->GetMousePos().x;
		prevMouse.y = INPUT->GetMousePos().y;
		isLbuttonDown = true;
	}
	if (INPUT->GetButtonUp(KEY_TYPE::RBUTTON))
		isLbuttonDown = false;
	if (isLbuttonDown)
	{
		Vec2 curMouse;
		curMouse.x = INPUT->GetMousePos().x;
		curMouse.y = INPUT->GetMousePos().y;

		float deltaX = (float)curMouse.x - prevMouse.x;
		float deltaY = (float)curMouse.y - prevMouse.y;

		camRotAngle.y += deltaX / 500.f;
		camRotAngle.x += deltaY / 500.f;

		if (camRotAngle.x < -XM_PI / 2.0f + 0.0001F)
			camRotAngle.x = -XM_PI / 2.0f + 0.0001F;
		if (camRotAngle.x > XM_PI / 2.0f - 0.0001F)
			camRotAngle.x = XM_PI / 2.0f - 0.0001F;

		prevMouse = curMouse;
	}

	Vec3 rot = GetTransform()->GetRotation();
	rot.x = camRotAngle.x;
	rot.y = camRotAngle.y;
	GetTransform()->SetRotation(rot);
}
