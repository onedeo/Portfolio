#include "CCollisionMgr.h"

#include "define.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
{

}
CCollisionMgr::~CCollisionMgr()
{

}


void CCollisionMgr::Init()
{
}

void CCollisionMgr::Update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (arrCheck[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}

}


void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurrentScene();
	
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);
	
	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		if (vecLeft[i]->getCollider() == nullptr) continue; //충돌체 없음
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			if (vecRight[j]->getCollider() == nullptr)continue; //충돌체 없음
			if (vecLeft[i] == vecRight[j]) continue; //충돌체가 자기 자신
			
			CCollider* pLeftcol = vecLeft[i]->getCollider();
			CCollider* pRightcol = vecRight[j]->getCollider();

			//두 충돌체 조합 아이디 생성
			COLLIDER_ID ID;
			ID.Left_id = pLeftcol->getID();
			ID.Right_id = pRightcol->getID();

			iter = mapColInfo.find(ID.ID);

			if (mapColInfo.end() == iter) //이전 프레임에 충돌 안했다. -> 충돌여부 미등록
			{
				mapColInfo.insert(make_pair(ID.ID, false));
				iter = mapColInfo.find(ID.ID);
			}

			if (IsCollision(pLeftcol, pRightcol)) //현재 충돌 if
			{
				if (iter->second) //전 프레임에도 충돌 했다
				{
					// 충돌중 하나가 죽음 -> 충돌하지 않은상태로 세팅
					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						pLeftcol->OnCollisionExit(pRightcol);
						pRightcol->OnCollisionExit(pLeftcol);
						iter->second = false;
					}
					else
					{
						pLeftcol->OnCollision(pRightcol);
						pRightcol->OnCollision(pLeftcol);
					}
				}
				else //첫 충돌
				{
					//둘 중 하나라도 죽지 않은 상태이면
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						pLeftcol->OnCollisionEnter(pRightcol);
						pRightcol->OnCollisionEnter(pLeftcol);
						iter->second = true;
					}
				}
			}
			else //충돌하지 않음
			{
				if (iter->second)
				{
					pLeftcol->OnCollisionExit(pRightcol);
					pRightcol->OnCollisionExit(pLeftcol);
					iter->second = false;
				}
				else
				{
					//전프레임에도, 지금도 충돌하지 않음
				}
			}
		}
	}

}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	Vec2 vLeftPos = _pLeftCol->getFinalPos();
	Vec2 vLeftScale = _pLeftCol->getScale();
	
	Vec2 vRightPos = _pRightCol->getFinalPos();
	Vec2 vRightScale = _pRightCol->getScale();

	if (abs(vRightPos.x - vLeftPos.x) < (vLeftScale.x + vRightScale.x) / 2.f
		&& abs(vRightPos.y - vLeftPos.y) < (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}


void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	//더 작은 값을 행으로

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;
	if (iCol < iRow)
	{
		UINT iCol= (UINT)_eLeft;
		UINT iRow = (UINT)_eRight;
	}


	if (arrCheck[iRow] & (1 << iCol))
	{
		arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		arrCheck[iRow] |= (1 << iCol);
	}
}

void CCollisionMgr::ResetGroup()
{
	memset(arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);
}

