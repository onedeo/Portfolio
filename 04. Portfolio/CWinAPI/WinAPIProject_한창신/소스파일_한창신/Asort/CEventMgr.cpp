#include "CEventMgr.h"
#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"

CEventMgr::CEventMgr()
{}
CEventMgr::~CEventMgr()
{}

void CEventMgr::Update()
{
	// >> : 이전 프레임 dead처리한거 삭제
	for (size_t i = 0; i < vecDead.size(); i++)
	{
		if (vecDead[i]->eGroup >= (GROUP_TYPE)0 && vecDead[i]->eGroup < GROUP_TYPE::END)
			delete vecDead[i];
	}
	vecDead.clear();
	// << : 이전 프레임 dead처리한거 삭제


	// >> : Event Execute
	for (size_t i = 0; i < vecEvent.size(); i++)
	{
		Execute(vecEvent[i]);
	}
	vecEvent.clear();
	// << : Event Execute
}

void CEventMgr::Execute(const tEvent& _eve)
{
	switch (_eve.eEvent)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		//	lParam : Object Address
		//	wParam: GROUP_TYPE
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE pNewGT = (GROUP_TYPE)_eve.wParam;
		CSceneMgr::GetInst()->GetCurrentScene()->AddObject(pNewObj, pNewGT);
	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:  //	Objectfmf Dead 상태로 변경 -> 한프레임 이후 실제 삭제
	{
		// lParam : Object Address
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->setDead();
		vecDead.push_back(pDeadObj);
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
		// lParam : Next Scene Type
		CSceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);
		break;
	case EVENT_TYPE::END:
		break;
	}
}


