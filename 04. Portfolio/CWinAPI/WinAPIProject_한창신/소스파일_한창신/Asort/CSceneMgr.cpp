#include "CSceneMgr.h"
#include "CScene_Start.h"
#include "Scene_Opening.h"
#include "Scene_Closing.h"
#include "CEventMgr.h"

CSceneMgr::CSceneMgr()
{

}
CSceneMgr::~CSceneMgr()
{
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; i++)
	{
		if (arrScene[i] != nullptr)
			delete arrScene[i];
	}
}

void CSceneMgr::Init()
{
	//¾À »ý¼º
	arrScene[(UINT)SCENE_TYPE::OPENING] = new Scene_Opening;
	arrScene[(UINT)SCENE_TYPE::OPENING]->set_Name(L"Opening Scene");
	
	arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	arrScene[(UINT)SCENE_TYPE::START]->set_Name(L"Start Scene");

	arrScene[(UINT)SCENE_TYPE::CLOSING] = new Scene_Closing;
	arrScene[(UINT)SCENE_TYPE::CLOSING]->set_Name(L"Closing Scene");

	//ÇöÀç ¾À
	crntScene = SCENE_TYPE::OPENING;
	//crntScene = SCENE_TYPE::CLOSING;
	pCurScene = arrScene[(UINT)crntScene];
	pCurScene->Enter();
}

void CSceneMgr::ChangeScene(SCENE_TYPE _scene)
{
	pCurScene->Exit();

	pCurScene = arrScene[(int)_scene];

	pCurScene->Enter();
}


void CSceneMgr::Update()
{
	pCurScene->Update();
	pCurScene->FinalUpdate();
}

void CSceneMgr::Render(HDC _dc)
{
	pCurScene->Render(_dc);
}

