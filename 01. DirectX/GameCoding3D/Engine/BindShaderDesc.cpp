#include "pch.h"
#include "BindShaderDesc.h"
#include "Camera.h"

void RenderManager::Init(shared_ptr<Shader> shader)
{
	_shader = shader;

}