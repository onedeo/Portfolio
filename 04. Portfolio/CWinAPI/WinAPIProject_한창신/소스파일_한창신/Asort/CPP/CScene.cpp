#include "../Header/CScene.h"
#include "../Header/CSceneMgr.h"
#include "../Header/func.h"

void CScene::Update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j=0;j<arrObj[i].size();j++)
		{
			if (!arrObj[i][j]->IsDead())
				arrObj[i][j]->Update();
			if (arrObj[i][j]->IsDead())
				int a = 0;
		}
	}
}

void CScene::FinalUpdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < arrObj[i].size(); j++)
		{
			arrObj[i][j]->FinalUpdate();
		}
	}
}

void CScene::Render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		vector<CObject*>::iterator iter = arrObj[i].begin();
		for(;iter!=arrObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->Render(_dc);
				iter++;
			}
			else
			{
				iter = arrObj[i].erase(iter);
			}
		}
	}
}

void CScene::DeleteGroup(GROUP_TYPE _eGroup)
{
	for (int i = 0; i < arrObj[(UINT)_eGroup].size(); i++)
	{
		if (nullptr != arrObj[(UINT)_eGroup][i])
			delete arrObj[(UINT)_eGroup][i];
	}
	arrObj[(UINT)_eGroup].clear();
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

CScene::CScene()
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (auto a : arrObj[i])
		{
			delete a;
		}
	}
}
