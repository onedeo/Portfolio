#pragma once
#include "Component.h"

enum class ProjectionType
{
	Perspective, //원근 투영 (멀리있는건 작게, 가까이 있는건 작게)
	Orthographic, //직교 투영 (영역에 들어오면 똑같은 크기로 보이게)
};

class Camera : public Component
{
	using Super = Component;
public:
	Camera();
	virtual ~Camera();

	virtual void Update() override;

	void SetProjectionType(ProjectionType type) { _type = type; }
	ProjectionType GetProjectionType() { return _type; }

	void UpdateMatrix();

private:
	ProjectionType _type = ProjectionType::Orthographic;

public:
	static Matrix S_MatView;
	static Matrix S_MatProjection;
};