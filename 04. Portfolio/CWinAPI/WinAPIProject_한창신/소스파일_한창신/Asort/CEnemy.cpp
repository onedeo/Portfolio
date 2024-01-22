#include <tchar.h>
#include "CEnemy.h"
#include "CMissile.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "define.h"
#include "CKeyMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CCore.h"

void CEnemy::Update()
{
	ocdCrnt = crntScene->GetOCD()->GetOCDCrnt();
	vCenter = GetPosition();
	vScale = GetScale();
	float dt = fDT;
	if (dt < 1)
	{
		fDTLeaf1 += dt;
		fDTIdle += dt;
		fDTSwamp += dt;
		fDTToCenter += dt;
	}

	if (fDTToCenter > 10)
	{
		eState = ENEMY_STATE::OUTBOUNDARY;
		ReturnToBoundary();
		fDTToCenter = 0;
	}
	if (!IsEnemyInOCD()|| eState == ENEMY_STATE::OUTBOUNDARY)
	{
		eState = ENEMY_STATE::OUTBOUNDARY;
		ReturnToBoundary();
		fSpeed = 300;
		vCenter.x += fDT * fSpeed * vDir.x;
		vCenter.y += fDT * fSpeed * vDir.y;
		SetPosition(vCenter);
		return;
	}

	if (fDTLeaf1 > fLeaf1Cycle&&!(eState==ENEMY_STATE::PARALYZED))
	{
		CreateRazorLeaf();
		fDTLeaf1 = 0;
	}
	if (fDTIdle > fIdleDuration)
	{
		EnemyIdle();
		fDTIdle = 0;
	}
	if (fDTSwamp > fSwampCycle)
	{
		CreateSwamp();
		fDTSwamp = 0;
	}
	if (eState == ENEMY_STATE::IDLE)
	{
		if (fDTIdle < 2) fSpeed = 250;
		else fSpeed = 150;
		vCenter.x += fDT * fSpeed * vDir.x;
		vCenter.y += fDT * fSpeed * vDir.y;
	}

	if (iSlowCount>0)
	{
		fDTRecoverSlow += fDT;
		if (iSlowCount > 5)
		{
			fSpeed = 0;
			eState = ENEMY_STATE::PARALYZED;
		}
		if (fDTRecoverSlow > 3)
		{
			iSlowCount = 0;
			fSpeed = fOriginalSpeed;
			eState = ENEMY_STATE::IDLE;
		}
	}


	OCDBounce();
	HitOCG();
	SetPosition(vCenter);
}

void CEnemy::Render(HDC _dc)
{
	SetScale(Vec2(pTex->getWidth(), pTex->getHeight()));
	Point pCenter = GetPosition();
	Point pScale = GetScale();
	pCenter.x -= (float)pScale.x / 2;
	pCenter.y -= (float)pScale.y / 2;

	TransparentBlt(_dc, pCenter.x, pCenter.y, pScale.x, pScale.y, pTex->getDC(), 0, 0, pScale.x, pScale.y, RGB(255, 255, 255));

	ComponentRender(_dc);

	//TCHAR point[20];
	//vCenter = GetPosition();
	//_stprintf_s(point, _T("(%.1f, %.1f)"), vCenter.x, vCenter.y);
	//TextOut(_dc, vCenter.x, vCenter.y, point, _tcslen(point));
}

CEnemy::CEnemy()
{
	Init();
}

CEnemy::~CEnemy()
{
}

void CEnemy::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->getOwnerObject()->getGroup() == GROUP_TYPE::PLAYER_PROJECTILE)
	{
		iSlowCount++;
		fSpeed *= 0.8;
		fDTRecoverSlow = 0;
	}
}

void CEnemy::OnCollision(CCollider* _pOther)
{

}

void CEnemy::OnCollisionExit(CCollider* _pOther)
{
}

void CEnemy::Init()
{
	pTex = CResMgr::GetInst()->LoadTexture(L"Bulbasaur", L"Texture\\monster\\bulbasaur\\bulbasaur_practice.bmp");
	wstring strFilePath = pTex->getRelativePath();
	strFilePath += L"Texture\\monster\\bulbasaur\\bulbasaur_practice.bmp";
	setGroup(GROUP_TYPE::MONSTER);

	pTex->setRelativePath(strFilePath);

	eState = ENEMY_STATE::IDLE;
	// >> : create componenets
	CreateCollider();
	getCollider()->setScale(Vec2(40, 30));
	// << : create componenets
	//EnemyIdle();

	crntScene = CSceneMgr::GetInst()->GetCurrentScene();
	ocdCrnt = crntScene->GetOCD()->GetOCDCrnt();

	fIdleDuration = 0;
	fOriginalSpeed = 150;
	fSpeed = 150;

	fSwampCycle = 10;
}

void CEnemy::CreateLeaf1(Vec2 _dir, float _fspeed)
{
	//씬 가져오기
	//CScene* pCurrentScene = CSceneMgr::GetInst()->GetCurrentScene();
	
	//미사일 생성 시간 설정

	CMissile* pMissile = new CMissile();
	pMissile->SetPosition(GetPosition());
	pMissile->InitLeaf1(_dir, _fspeed);
	
	CreateObject(pMissile, GROUP_TYPE::MONSTER_PROJECTILE);
	fLeaf1Cycle = (rand() % 3) + 2;
}

void CEnemy::EnemyIdle()
{
	eState = ENEMY_STATE::IDLE;
	//vDir = Vec2(rand() % 200 - 100, rand() % 200 - 100);
	Vec2 vPlayer = crntScene->GetPlayer()->GetPosition();
	Vec2 newDir = Vec2(vPlayer.x - vCenter.x, vPlayer.y - vCenter.y);
	vDir = (newDir);
	if (vDir.x == 0) vDir.x = 1;
	if (vDir.y == 0) vDir.y = 1;
	vDir.Normalize();
	fIdleDuration = rand() % 5 + 3;
}

void CEnemy::OCDBounce()
{
	

	Point pCenter = vCenter.ToPoint();
	int radius = 100;

	OCDPoint* temp = ocdCrnt;
	do
	{
		if (IsBetweenY(ocdCrnt->pPoint, ocdCrnt->nxt->pPoint, pCenter))
		{
			if (IsBetweenTwo(ocdCrnt->pPoint.x + radius, ocdCrnt->pPoint.x - radius, pCenter.x))
				vDir.x *= -1;
		}
		if (IsBetweenX(ocdCrnt->pPoint, ocdCrnt->nxt->pPoint, pCenter))
		{
			if (IsBetweenTwo(ocdCrnt->pPoint.y + radius, ocdCrnt->pPoint.y - radius, pCenter.y))
				vDir.y *= -1;
		}
		ocdCrnt = ocdCrnt->nxt;
	} while (ocdCrnt != temp);

	/*
	int radius = 50;
	Point pCenter = vCenter.ToPoint();

	RECT rect = CCore::GetInst()->GetOCDTotalSize();

	if (pCenter.x - radius < rect.left || pCenter.x + radius>rect.right)
		vDir.x *= -1;
	if (pCenter.y + radius > rect.bottom || pCenter.y - radius < rect.top)
		vDir.y *= -1;
		*/
}

bool CEnemy::IsEnemyInOCD()
{
		int enemyLineCnt = 0;

		OCDPoint* temp = ocdCrnt;

		//몬스터 좌우위아래 중 ocg 선이 홀수면 in 짝수면 out
		DIRECTION startCnt = DIRECTION::END;
		do
		{
			if ((startCnt == DIRECTION::END || startCnt == DIRECTION::RIGHT) && vCenter.x < ocdCrnt->pPoint.x)
			{
				if (IsBetweenY(ocdCrnt->pPoint, ocdCrnt->nxt->pPoint, vCenter))
				{
					enemyLineCnt++;
					startCnt = DIRECTION::RIGHT;
				}
			}
			if ((startCnt == DIRECTION::END || startCnt == DIRECTION::LEFT) && vCenter.x > ocdCrnt->pPoint.x)
			{
				if (IsBetweenY(ocdCrnt->pPoint, ocdCrnt->nxt->pPoint, vCenter))
				{
					enemyLineCnt++;
					startCnt = DIRECTION::LEFT;
				}
			}
			if ((startCnt == DIRECTION::END || startCnt == DIRECTION::DOWN) && vCenter.y < ocdCrnt->pPoint.y)
			{
				if (IsBetweenX(ocdCrnt->pPoint, ocdCrnt->nxt->pPoint, vCenter))
				{
					enemyLineCnt++;
					startCnt = DIRECTION::DOWN;
				}
			}
			if ((startCnt == DIRECTION::END || startCnt == DIRECTION::UP) && vCenter.y > ocdCrnt->pPoint.y)
			{
				if (IsBetweenX(ocdCrnt->pPoint, ocdCrnt->nxt->pPoint, vCenter))
				{
					enemyLineCnt++;
					startCnt = DIRECTION::UP;
				}
			}

			ocdCrnt = ocdCrnt->nxt;
		} while (temp != ocdCrnt);
		if (enemyLineCnt % 2 != 0)
		{
			return true;
		}
		return false;
}

void CEnemy::ReturnToBoundary()
{
	float sumX = 0;
	float sumY = 0;
	int ocdCount = 0;
	OCDPoint* temp = ocdCrnt;
	do
	{
		sumX += ocdCrnt->pPoint.x;
		sumY += ocdCrnt->pPoint.y;
		ocdCount++;

		ocdCrnt = ocdCrnt->nxt;
	} while (temp != ocdCrnt);

	Vec2 OCDCenter=Vec2(sumX / ocdCount, sumY / ocdCount);
	vDir = Vec2(OCDCenter.x - vCenter.x, OCDCenter.y - vCenter.y);
	vDir.Normalize();

	Vec2 lefttop = Vec2(OCDCenter.x - 10, OCDCenter.y - 10);
	Vec2 rightbot = Vec2(OCDCenter.x + 10, OCDCenter.y + 10);

	if (IsBetweenX(lefttop, rightbot, vCenter) && IsBetweenY(lefttop, rightbot, vCenter))
		eState = ENEMY_STATE::IDLE;
}

void CEnemy::CreateRazorLeaf()
{
	fDTRazorLeaf = fDTLeaf1;
	Vec2 vVectorTo;
	for (int i = 0; i < 10; i++)
	{
		vVectorTo = Vec2(rand() % 200 - 100, rand() % 200 - 100);
		CreateLeaf1(vVectorTo, 10);
	}
}

void CEnemy::CreateSwamp()
{
	CMissile* pMissile = new CMissile();
	pMissile->SpreadSwamp();

	CreateObject(pMissile, GROUP_TYPE::PLAYER_DEBUFF);
	fSwampCycle = 10 + rand() % 5;
}


void CEnemy::HitOCG()
{
	CScene* crntScene = CSceneMgr::GetInst()->GetCurrentScene();
	PackOCG packOCG = crntScene->GetPlayer()->GetOCGPack();
	Point pCenter = vCenter.ToPoint();
	Point pScale = GetScale();
	int radius =50;
	for (int i = 0; i < packOCG.ocgCnt; i++)
	{
		if (IsBetweenY(packOCG.ocgPoint[i], packOCG.ocgPoint[i + 1], pCenter))
		{ 
			if (IsBetweenTwo(packOCG.ocgPoint[i].x + radius, packOCG.ocgPoint[i].x - radius, pCenter.x))
 				crntScene->GetPlayer()->GoBackOCG0();
		}
		if (IsBetweenX(packOCG.ocgPoint[i], packOCG.ocgPoint[i + 1], pCenter))
		{
			if (IsBetweenTwo(packOCG.ocgPoint[i].y + radius, packOCG.ocgPoint[i].y - radius, pCenter.y))
				crntScene->GetPlayer()->GoBackOCG0();
		}
	}
}
