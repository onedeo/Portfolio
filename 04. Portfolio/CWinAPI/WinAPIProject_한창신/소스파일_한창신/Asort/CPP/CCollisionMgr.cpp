#include "../Header/CCollisionMgr.h"

#include "../Header/define.h"
#include "../Header/CSceneMgr.h"
#include "../Header/CScene.h"
#include "../Header/CObject.h"
#include "../Header/CCollider.h"

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
		if (vecLeft[i]->getCollider() == nullptr) continue; //�浹ü ����
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			if (vecRight[j]->getCollider() == nullptr)continue; //�浹ü ����
			if (vecLeft[i] == vecRight[j]) continue; //�浹ü�� �ڱ� �ڽ�
			
			CCollider* pLeftcol = vecLeft[i]->getCollider();
			CCollider* pRightcol = vecRight[j]->getCollider();

			//�� �浹ü ���� ���̵� ����
			COLLIDER_ID ID;
			ID.Left_id = pLeftcol->getID();
			ID.Right_id = pRightcol->getID();

			iter = mapColInfo.find(ID.ID);

			if (mapColInfo.end() == iter) //���� �����ӿ� �浹 ���ߴ�. -> �浹���� �̵��
			{
				mapColInfo.insert(make_pair(ID.ID, false));
				iter = mapColInfo.find(ID.ID);
			}

			if (IsCollision(pLeftcol, pRightcol)) //���� �浹 if
			{
				if (iter->second) //�� �����ӿ��� �浹 �ߴ�
				{
					// �浹�� �ϳ��� ���� -> �浹���� �������·� ����
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
				else //ù �浹
				{
					//�� �� �ϳ��� ���� ���� �����̸�
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{
						pLeftcol->OnCollisionEnter(pRightcol);
						pRightcol->OnCollisionEnter(pLeftcol);
						iter->second = true;
					}
				}
			}
			else //�浹���� ����
			{
				if (iter->second)
				{
					pLeftcol->OnCollisionExit(pRightcol);
					pRightcol->OnCollisionExit(pLeftcol);
					iter->second = false;
				}
				else
				{
					//�������ӿ���, ���ݵ� �浹���� ����
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
	//�� ���� ���� ������

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

