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
#include "Portfolio1.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	GameDesc desc;
	desc.appName = L"GameCoding3D";
	desc.hInstance = hInstance;
	desc.vsync = false;
	desc.hWnd = NULL;
	desc.width = 1200;
	desc.height = 800;
	desc.clearColor = Color(0.f, 0.2f, 0.f, 0.f);
	desc.app = make_shared<Portfolio1>();

	GAME->Run(desc);

	return 0;
}