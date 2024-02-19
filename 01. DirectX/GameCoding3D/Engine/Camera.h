#pragma once
#include "Component.h"

enum class ProjectionType
{
	Perspective, //���� ���� (�ָ��ִ°� �۰�, ������ �ִ°� �۰�)
	Orthographic, //���� ���� (������ ������ �Ȱ��� ũ��� ���̰�)
};

class Camera : public Component
{
	using Super = Component;
public:
	Camera();
	virtual ~Camera();

	virtual void Update() override;
	void UpdateMatrix();

	ProjectionType GetProjectionType() { return _type; }
	float SetNear(float value) { _near = value; }
	float Setfar(float value) { _far = value; }
	float SetFOV(float value) { _fov = value; }
	float SetWidth(float value) { _width= value; }
	float SetHeight(float value) { _height= value; }	

	void SetProjectionType(ProjectionType type) { _type = type; }

	Matrix& GetViewMatrix() { return _matView; }
	Matrix& GetProjectionMatrix() { return _matProjection; }		
	
private:
	ProjectionType _type = ProjectionType::Perspective;

private:
	Matrix _matView = Matrix::Identity;
	Matrix _matProjection = Matrix::Identity;

	float _near = 1.f;
	float _far = 1000.f;
	float _fov = XM_PI / 4.f;
	float _width = 0.f;
	float _height = 0.f;

public:
	static Matrix S_MatView; //ī�޶� SRT
	static Matrix S_MatProjection; // ī�޶� ���� ���� ���
};