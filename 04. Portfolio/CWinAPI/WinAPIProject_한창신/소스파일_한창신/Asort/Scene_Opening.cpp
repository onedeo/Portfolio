#include "Scene_Opening.h"
#include "Opening.h"

Scene_Opening::Scene_Opening()
{

}

Scene_Opening::~Scene_Opening()
{
}

void Scene_Opening::Enter()
{
	Opening* obj = new Opening;
	AddObject(obj, GROUP_TYPE::UI);
}

void Scene_Opening::Exit()
{
	DeleteAll();
}
