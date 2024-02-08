#include "pch.h"
#include "Camera.h"

Matrix Camera::S_MatProjection = Matrix::Identity;
Matrix Camera::S_MatView = Matrix::Identity;

Camera::Camera() : Super(ComponentType::Camera)
{
	_width = static_cast<float>(GAME->GetGameDesc().width);
	_height= static_cast<float>(GAME->GetGameDesc().height);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	UpdateMatrix();

	RENDER->PushGlobalData(Camera::S_MatView, Camera::S_MatProjection);
}

void Camera::UpdateMatrix()
{
	//view�� projection ��� �����ش�

	//view �����ֱ�
	//S_MatView = Matrix::Identity; //-> world �� ��ġ Transform 0
	
	// >> : �Ʒ� 2�� �� �ϳ��� view ���� �� �ִ� 
	Vec3 eyePosition = GetTransform()->GetPosition();
	Vec3 focusPosition = eyePosition + GetTransform()->GetLook();
	Vec3 upDirection = GetTransform()->GetUp();
	S_MatView = ::XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);

	//S_MatView = GetTransform()->GetWorldMatrix().Invert(); //dī�޶� �������� ��ü�� ���� -> ��ü * ī�޶����
	// << : 

	if (_type == ProjectionType::Perspective)
		S_MatProjection = ::XMMatrixPerspectiveFovLH(XM_PI / 4.f, 800.f / 600.f, 1.f, 100.f);
	else
		S_MatProjection = XMMatrixOrthographicLH(_fov, _width / _height, _near, _far);
}
