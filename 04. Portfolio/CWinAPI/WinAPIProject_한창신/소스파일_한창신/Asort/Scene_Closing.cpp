#include "Scene_Closing.h"
#include "CKeyMgr.h"
#include "CClosing.h"
Scene_Closing::Scene_Closing()
{
}

Scene_Closing::~Scene_Closing()
{
}

void Scene_Closing::Enter()
{
	CClosing* obj = new CClosing;
	AddObject(obj, GROUP_TYPE::UI);
}

void Scene_Closing::Exit()
{
	DeleteAll();
}
