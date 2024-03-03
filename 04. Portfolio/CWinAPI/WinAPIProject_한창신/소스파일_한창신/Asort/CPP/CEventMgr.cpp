#include "../Header/CEventMgr.h"
#include "../Header/CObject.h"
#include "../Header/CSceneMgr.h"
#include "../Header/CScene.h"

CEventMgr::CEventMgr()
{}
CEventMgr::~CEventMgr()
{}

void CEventMgr::Update()
{
	// >> : ���� ������ deadó���Ѱ� ����
	for (size_t i = 0; i < vecDead.size(); i++)
	{
		if (vecDead[i]->eGroup >= (GROUP_TYPE)0 && vecDead[i]->eGroup < GROUP_TYPE::END)
			delete vecDead[i];
	}
	vecDead.clear();
	// << : ���� ������ deadó���Ѱ� ����


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
	case EVENT_TYPE::DELETE_OBJECT:  //	Objectfmf Dead ���·� ���� -> �������� ���� ���� ����
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


