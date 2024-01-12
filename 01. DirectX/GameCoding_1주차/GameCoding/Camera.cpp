#include "pch.h"
#include "Camera.h"

Matrix Camera::S_MatProjection = Matrix::Identity;
Matrix Camera::S_MatView = Matrix::Identity;

Camera::Camera() : Super(ComponentType::Camera)
{
}

Camera::~Camera()
{
}

void Camera::Update()
{
	UpdateMatrix();
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

	//S_MatView = GetTransform()->GetWorldMatrix().Invert(); //ī�޶� �������� ��ü�� ���� -> ��ü * ī�޶����
	// << : 

	if (_type == ProjectionType::Perspective)
		S_MatProjection = ::XMMatrixPerspectiveFovLH(XM_PI / 4.f, 800.f / 600.f, 1.f, 100.f);
	else
		XMMatrixOrthographicLH(800, 600, 0.f, 1.f);
}
