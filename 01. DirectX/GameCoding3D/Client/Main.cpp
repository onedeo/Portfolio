#include "pch.h"
#include "Main.h"
#include "Engine/Game.h"
#include "BasicShapes.h"
#include "LightingMaterial.h"
#include "21. ModelInstancingDemo.h"
#include "22. AnimInstancingDemo.h"
#include "23. RenderDemo.h"
#include "24. SceneDemo.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	GameDesc desc;
	desc.appName = L"GameCoding3D";
	desc.hInstance = hInstance;
	desc.vsync = false;
	desc.hWnd = NULL;
	desc.width = 800;
	desc.height = 600;
	desc.clearColor = Color(0.f, 0.2f, 0.f, 0.f);
	desc.app = make_shared<SceneDemo>(); //������ ���� �־��ָ�ȴ� : ���� ����

	GAME->Run(desc);

	return 0;
}