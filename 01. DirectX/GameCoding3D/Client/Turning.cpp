#include "pch.h"
#include "Turning.h"
#include "GameObject.h"

void Turning::Update()
{
	GetTransform()->SetLocalRotation(GetTransform()->GetLocalRotation() + Vec3(0, 1 * TIME->GetDeltaTime(), 1*TIME->GetDeltaTime()));
}
