#include "pch.h"
#include "Main.h"
#include "Engine/Game.h"
#include "BasicShapes.h"
#include "LightingMaterial.h"
#include "Instancing.h"
#include "25. RawBufferDemo.h"
#include "26. GroupDemo.h"
#include "27. TextureBufferDemo.h"
#include "28. StructuredBufferDemo.h"
#include "29. ViewportDemo.h"
#include "30. CollisionDemo.h"

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
	desc.app = make_shared<CollisionDemo>(); //실행할 앱을 넣어주면된다 : 실행 단위

	GAME->Run(desc);

	return 0;
}