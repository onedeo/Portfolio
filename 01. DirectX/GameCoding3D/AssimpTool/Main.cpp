#include "pch.h"
#include "Main.h"
#include "Engine/Game.h"
#include "AssimpTool.h"
#include "01. StaticMeshDemo.h"
#include "02. ImGUIDemo.h"

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
	//desc.app = make_shared<ImGUIDemo>();
	//desc.app = make_shared<StaticMeshDemo>(); 
	desc.app = make_shared<AssimpTool>(); 

	GAME->Run(desc);

	return 0;
}