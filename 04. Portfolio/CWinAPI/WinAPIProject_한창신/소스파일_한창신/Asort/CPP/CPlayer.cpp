#include <tchar.h>
#include "../Header/pch.h"
#include "../Header/CCore.h"
#include "../Header/CPlayer.h"
#include "../Header/CMissile.h"
#include "../Header/CSceneMgr.h"
#include "../Header/CScene.h"
#include "../Header/CPathMgr.h"
#include "../Header/CResMgr.h"
#include "../Header/CCollider.h"
#include "../Header/CKeyMgr.h"
#include "../Header/CObject.h"
#include "../Header/SelectGDI.h"
#include "../Header/CPokemon.h"
#include "../Header/CScene_Start.h"

//class COcuppied;

CPlayer::CPlayer()
	: pTex(nullptr)
{
	setGroup(GROUP_TYPE::PLAYER);
	// >> : load character image
	pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTexture", L"Texture\\player\\playermovement_practice.bmp");
	wstring strFilepath = CPathMgr::GetInst()->getContentPath();
	strFilepath += L"Texture\\player\\playermovement_practice.bmp";

	pTex->Load(strFilepath);
	// << : load character image

	// >> : create componenets
	CreateCollider();
	getCollider()->setScale(Vec2(30, 40));
	getCollider()->setOffsetPos(Vec2(5, 4));

	// << : create componenets
}
CPlayer::~CPlayer()
{
}
void CPlayer::ResetToStart()
{
	eState = PLAYER_STATE::ON_OCCUPIED;
	// >> : set Player random position of OCD
	RECT rect = CCore::GetInst()->GetOCDTotalSize();
	DIRECTION dir = (DIRECTION)(rand() % (int)DIRECTION::END);
	int x = rand() % (rect.right - rect.left - 500) + 200;
	int y = rand() % (rect.bottom - rect.top - 500) + 200;
	dir = DIRECTION(rand() % (int)DIRECTION::END);
	if (dir == DIRECTION::UP)
		y = rect.top;
	else if (dir == DIRECTION::DOWN)
		y = rect.bottom;
	else if (dir == DIRECTION::RIGHT)
		x = rect.right;
	else if (dir == DIRECTION::LEFT)
		x = rect.left;
	SetPosition(Vec2(x, y));
	// <<: set Player random position of OCD

	int iStage = CCore::GetInst()->GetStage();
	switch (iStage)
	{
		case 5:
		case 4:
		case 3:
		case 2:
		case 1:
			CPokemon * pPokemon = new CPokemon;
			pPokemon->Init();
			CreateObject(pPokemon, GROUP_TYPE::POKEMON);
			pokemon = pPokemon;
			break;
	}
	OCGonOCD = false;
	fdefaultfSpeed = 100;
	fSpeed = fdefaultfSpeed;
	ocgCnt = 0;
	fRetreatSpeed = 0.8;
	fStamina = 50;
	fRecoverStamina = 20;
	iLife = 3;
}

void CPlayer::Update()
{	
	vCenter = GetPosition();
	vScale = GetScale();
	if (KEY_HOLD(KEY::Q)) return;

	pCenter = GetPosition().ToPoint();
	eDirBefore = eDirCrnt;

	MovementUpdate();
	SpaceKeyUpdate();
	bRetreat = false;

	if (KEY_TAP(KEY::TAB))
	{
		PirntOCDDirection();	
		
		printf("On OCD?: %d\n", IsPlayerOnOCD());
		//printf("ocd: %d,%d\n", pOCGPoint[0].x, pOCGPoint[0].y);
		PrintState();
		//printf("Player Moved: %.3f, %.3f\n", pOCGPoint[0].x - vCenter.x, pOCGPoint[0].y - vCenter.y);
		/*printf("%.5f\n", fDT);
		printf("%.5f\n", fTotSpeed);
		printf("%.5f\n", fCrntSpeed);*/
		printf("player: %.3f, %.3f\n", vCenter.x, vCenter.y);
		printf("OCG[0]=%df, %d\n", pOCGPoint[0].x, pOCGPoint[0].y);
		printf("\n");


	}

	
	// >> : State Update
	if (!moved||eState==PLAYER_STATE::ON_OCCUPIED)
	{
		if(fStamina<50)
		fStamina += fRecoverStamina * fDT;
	}
	

	if (KEY_HOLD(KEY::LSHIFT))
	{
		if (fStamina > 0)
			bRunning = true;
		else bRunning=false;

		if(fStamina>0&&moved)
		fStamina -= fRecoverStamina * 1.5 * fDT;
	}
	if (KEY_AWAY(KEY::LSHIFT))
	{
		bRecoverStamina = true;
		bRunning = false;
	}

	if (KEY_TAP(KEY::Q))
		CollectOCGPoints();
	if(eState==PLAYER_STATE::READY_OCG)
	{
		OCDPoint* ocdPoint = GetOCDVec2();
		OCDPoint* temp = ocdPoint;
		do
		{
			if (ocdPoint->pPoint.AroundEqual(pCenter))
			{
				pOCGPoint[0] = ocdPoint->pPoint;
				OCGonOCD = true;
				break;
			}
			else
				OCGonOCD = false;
			ocdPoint = ocdPoint->nxt;
		} while (ocdPoint != temp);

		if (!OCGonOCD)
			pOCGPoint[0] = vCenter;

		
		//printf("pOCGPoint[0]= %d, %d\n", pOCGPoint->x, pOCGPoint->y);
		ocdPoint = ocdPoint->nxt;
		bCollect = true;
		eDirStart = DIRECTION::END;
	}
 	else if (eState == PLAYER_STATE::OCCUPYING)
	{
		if (eDirStart == DIRECTION::END)
		{
			eDirStart = eDirCrnt;
			ocgCnt = 1;
		}

		CollectOCGPoints();

		if (IsPlayerOnOCD())
		{
			
			eState = PLAYER_STATE::ON_OCCUPIED;

			OCDPoint* ocdCrnt = GetOCDVec2();
			OCDPoint* temp = ocdCrnt;
			do
			{
				if (IsBetweenX(ocdCrnt->pPoint, ocdCrnt->nxt->pPoint, pOCGPoint[ocgCnt]))
				{
					if (abs(ocdCrnt->pPoint.y - pOCGPoint[ocgCnt].y) <= 1
						&& abs(ocdCrnt->pPoint.y - pOCGPoint[ocgCnt].y) >= 0)
						pOCGPoint[ocgCnt].y = ocdCrnt->pPoint.y;
				}
				if (IsBetweenY(ocdCrnt->pPoint, ocdCrnt->nxt->pPoint, pCenter))
				{
					if (abs(ocdCrnt->pPoint.x - pOCGPoint[ocgCnt].x) <= 1
						&& abs(ocdCrnt->pPoint.x - pOCGPoint[ocgCnt].x) >= 0)
						pOCGPoint[ocgCnt].x = ocdCrnt->pPoint.x;
				}
			} while (ocdCrnt != temp);
				ocgCnt++;

			CScene* crntScene = CSceneMgr::GetInst()->GetCurrentScene();
			crntScene->GetOCD()->FinishOCG(GetOCGPack());
			OCGonOCD = false;
			ocgCnt = 0;
		}
	}
	else if (eState == PLAYER_STATE::GOBACK)
	{
		bRetreat = true;
		if (IsPlayerOnOCD())
		{
			eState = PLAYER_STATE::ON_OCCUPIED;
			ocgCnt = 0;
		}
		else 	MoveGoBack();
		/*if (!moved)
			vCenter = pOCGPoint[0].ToVec2();*/
	}
	

	// << : State Update

	GetOCGPack();
	SetPosition(vCenter);
}
void CPlayer::Render(HDC _dc)
{

	// >> : draw character image
	SetScale(Vec2(pTex->getWidth(), pTex->getHeight()));

	Point pDraw = GetPosition();
	Point pScale = GetScale();
	pDraw.x -= round((float)pScale.x / 2);
	pDraw.y -= round((float)pScale.y / 2);
	TransparentBlt(_dc, pDraw.x, pDraw.y, pScale.x, pScale.y, pTex->getDC(), 0, 0, pScale.x, pScale.y, RGB(255, 0, 255));
	// << : draw character image

	// >> : Render Stamina Gage
	Point pStart = { vCenter.x - 30, vCenter.y - 35 };
	Point pYellow = { 60 * (1 - (fStamina / 50)), 10 };

	RECT rectGage = { pStart.x, pStart.y,pStart.x + 60,pStart.y + 10 };
	RECT rectBlue = { pStart.x,pStart.y, pStart.x + pYellow.x,pStart.y + pYellow.y };
	Rectangle(_dc, rectGage.left, rectGage.top, rectGage.right, rectGage.bottom);
	SelectGDI brush(_dc, BRUSH_TYPE::BLUE);
	Rectangle(_dc, rectBlue.left, rectBlue.top, rectBlue.right, rectBlue.bottom);
	// << : Render Stamina Gage

	// >> : Render Life

	// << : Render Life

	// >> : Print Player Position
	TCHAR point[20];
	//vCenter = GetPosition();
	//_stprintf_s(point, _T("(%.1f, %.1f)"), vCenter.x, vCenter.y);
	//TextOut(_dc, vCenter.x, vCenter.y, point, _tcslen(point));
	// << : Print Player Position

	// >> : Draw OCG Line
	PEN_TYPE ePen;
	ePen = PEN_TYPE::BLUE;
	SelectGDI pen(_dc, ePen);

	if(eState==PLAYER_STATE::OCCUPYING|| eState == PLAYER_STATE::GOBACK)
	{
		point[20];
		for (int i = 0; i < ocgCnt; i++)
		{
			/*_stprintf_s(point, _T("(%d, %d)"), pOCGPoint[i].x, pOCGPoint[i].y);
			TextOut(_dc, pOCGPoint[i].x, pOCGPoint[i].y, point, _tcslen(point));*/

			MoveToEx(_dc, pOCGPoint[i].x, pOCGPoint[i].y, NULL);
			LineTo(_dc, pOCGPoint[i + 1].x, pOCGPoint[i + 1].y);
		}
	}
	// << : Draw OCG Line

	// >> : Draw Pikachu Distance
	if (KEY_HOLD(KEY::Q))
	{
		PEN_TYPE ePen;
		ePen = PEN_TYPE::YELLOW;
		BRUSH_TYPE eBrush;
		eBrush = BRUSH_TYPE::HOLLOW;
		SelectGDI pen(_dc, ePen);
		SelectGDI brush(_dc, eBrush);
		Vec2 vNewCen = { vCenter.x - 120, vCenter.y - 120};
		Ellipse(_dc, vNewCen.x, vNewCen.y, vNewCen.x + 240, vNewCen.y + 240);
	}
	// << : Draw Pikachu Distance




	ComponentRender(_dc);
}

// >> : Space Key
void CPlayer::SpaceKeyUpdate()
{
	if (KEY_TAP(KEY::SPACE)) 
	{
 		if (eState == PLAYER_STATE::ON_OCCUPIED)
			eState = PLAYER_STATE::READY_OCG;
	}
	if (KEY_HOLD(KEY::SPACE))
	{
		//READY_OCG�� OCCUPYING is depend on "is player in safe place"
		if (IsPlayerOnOCD() && eState != PLAYER_STATE::OCCUPYING)
		{
			eState = PLAYER_STATE::READY_OCG;
		}	
		else if (eState == PLAYER_STATE::ON_OCCUPIED)
			KEY_TAP(KEY::SPACE);
		else
		{
			eState = PLAYER_STATE::OCCUPYING; 
		}
	}
	if (KEY_AWAY(KEY::SPACE))
	{
		if (eState == PLAYER_STATE::READY_OCG)
			eState = PLAYER_STATE::ON_OCCUPIED;

		else if (eState == PLAYER_STATE::OCCUPYING)
		{
			MoveGoBack();
			if(IsPlayerOnOCD())
				eState = PLAYER_STATE::ON_OCCUPIED;
			eState = PLAYER_STATE::GOBACK;
		}

		OCDPoint* temp = GetOCDVec2();
		//printf("%d\n", CountLinesOnDirection(vCenter, temp, eDirCrnt));
	}
}
// << : Space Key

// >> : Player Move On States
void CPlayer::MovementUpdate()
{
	SetSpeed();
	moved = false;
	ConfigOCDDir();
	if (eState==PLAYER_STATE::ON_OCCUPIED)
	{
		MoveOnOCD();
	}
	else if (eState == PLAYER_STATE::READY_OCG)
	{
		MoveOnOCD();
		if (!moved)
			MoveReadyOCG();
	}ㅌ
	else if (eState == PLAYER_STATE::OCCUPYING)
	{
		MoveOccupying();
	}
	else if (eState == PLAYER_STATE::GOBACK)
	{
		if(!moved)
		MoveGoBack();
	}
}
void CPlayer::MoveOnOCD()
{
	if (KEY_HOLD(KEY::LEFT))
	{
		if (OCDDir[(int)DIRECTION::LEFT] != nullptr)
			MoveLeft();
	}
	if (KEY_HOLD(KEY::RIGHT))	
	{
		if (OCDDir[(int)DIRECTION::RIGHT] != nullptr)
			MoveRight();
	}
	if (KEY_HOLD(KEY::UP))
	{
		if (OCDDir[(int)DIRECTION::UP] != nullptr)
			MoveUp();
	}
	if (KEY_HOLD(KEY::DOWN))
	{
		if (OCDDir[(int)DIRECTION::DOWN] != nullptr)
			MoveDown();
	}
	PreventPlayerExceed();
}
void CPlayer::MoveReadyOCG()
{
	int count;
	if (KEY_HOLD(KEY::RIGHT))
	{
		// ������ ocd ���� ī��Ʈ �ؼ� ¦���� ������ Ȧ���� �� �� �ֵ���
		count = CountLinesOnDirection(vCenter.ToPoint(), GetOCDVec2(), DIRECTION::RIGHT);
		if (count != 0 && count % 2 != 0)
			MoveRight();
	}
	if (KEY_HOLD(KEY::LEFT))
	{
		count = CountLinesOnDirection(vCenter.ToPoint(), GetOCDVec2(), DIRECTION::LEFT);
		if (count != 0 && count % 2 != 0)
			MoveLeft();
	}
	if (KEY_HOLD(KEY::UP))
	{
		count = CountLinesOnDirection(vCenter.ToPoint(), GetOCDVec2(), DIRECTION::UP);
		if (count != 0 && count % 2 != 0)
			MoveUp(); 
	}
	if (KEY_HOLD(KEY::DOWN))
	{
 		count = CountLinesOnDirection(vCenter.ToPoint(), GetOCDVec2(), DIRECTION::DOWN);
		if (count != 0 && count % 2 != 0)
			MoveDown();
	}
	PreventPlayerExceed();
}
void CPlayer::MoveOccupying()
{		
	if (KEY_HOLD(KEY::RIGHT))
	{
		if(!IsOCGExceed(Point(pCenter.x+1,pCenter.y)))
		MoveRight();
	}
	else if (KEY_HOLD(KEY::LEFT))
	{
		if (!IsOCGExceed(Point(pCenter.x - 1, pCenter.y)))
		MoveLeft();
	}
	else if (KEY_HOLD(KEY::UP))
	{
		if (!IsOCGExceed(Point(pCenter.x, pCenter.y-1)))
		MoveUp();
	}
	else if (KEY_HOLD(KEY::DOWN))
	{
		if (!IsOCGExceed(Point(pCenter.x, pCenter.y + 1)))
		MoveDown();
	}
	if (moved)
	{
		PreventPlayerExceed();
		if (!bCollect)
		{
			if(eDirBefore==eDirCrnt||eDirBefore==OppositeDirection(eDirCrnt))
				eDirBefore = eDirCrnt;
			bCollect = true;
		}
	}
}
void CPlayer::MoveGoBack()
{
	Point vLastOcg = pOCGPoint[ocgCnt - 1];
	Point v_iPos = { Vec2(vCenter.x, vCenter.y).ToPoint()};
	if (eState == PLAYER_STATE::OCCUPYING)
	{
		vCenter = pOCGPoint[ocgCnt].ToVec2();
		eState = PLAYER_STATE::GOBACK;
	}
	else if (eState==PLAYER_STATE::GOBACK)
	{
		if (ocgCnt == 0)
		{
			vCenter = pOCGPoint[0].ToVec2();
		}
		if ((int)vLastOcg.x == (int)v_iPos.x)
		{
			if ((int)vLastOcg.y == (int)v_iPos.y)
				ocgCnt--;
			else if ((int)vLastOcg.y > (int)v_iPos.y)
				MoveDown();
			else
				MoveUp();
		}
		else if ((int)vLastOcg.y == (int)v_iPos.y)
		{
			if ((int)vLastOcg.x == (int)v_iPos.x)
				ocgCnt--;
			else if ((int)vLastOcg.x > (int)v_iPos.x)
				MoveRight();
			else
				MoveLeft();
		}
	}
	pOCGPoint[ocgCnt] = v_iPos; 
	bCollect = false;
}
// << : Player Move On States

// >> : Player On OCG
void CPlayer::CollectOCGPoints( )
{
 	if (eDirBefore != eDirCrnt && eDirBefore != OppositeDirection(eDirCrnt))
	{
 		pOCGPoint[ocgCnt] = vCenter;
	 	if (abs(pOCGPoint[ocgCnt].x - pOCGPoint[ocgCnt - 1].x) == 1)
		{
			pOCGPoint[ocgCnt].x = pOCGPoint[ocgCnt - 1].x;
		}
		else if (abs(pOCGPoint[ocgCnt].y - pOCGPoint[ocgCnt - 1].y) == 1)
		{
			pOCGPoint[ocgCnt].y = pOCGPoint[ocgCnt - 1].y;
		}
		ocgCnt++; 
	}
	else
	{
		pOCGPoint[ocgCnt] = vCenter.ToPoint();
	}
}
void CPlayer::DeleteOCGPoint()
{
}
void CPlayer::ConfigOCGDir()
{
	for(int i=0; i<ocgCnt;i++)
	{
		if (IsBetweenX(pOCGPoint[i], pOCGPoint[i + 1], vCenter))
		{
			if (vCenter.x > pOCGPoint[i].x)
			{
				OCGDir[(int)DIRECTION::LEFT] = pOCGPoint[i];
				OCGDir[(int)DIRECTION::RIGHT] = pOCGPoint[i + 1];
			}
			else
			{
				OCGDir[(int)DIRECTION::LEFT] = pOCGPoint[i + 1];
				OCGDir[(int)DIRECTION::RIGHT] = pOCGPoint[i];
			}
		}
		else if (IsBetweenY(pOCGPoint[i], pOCGPoint[i+1], vCenter))
		{
			if (vCenter.y >= pOCGPoint[i].y)
			{
				OCGDir[(int)DIRECTION::UP] = pOCGPoint[i];
				OCGDir[(int)DIRECTION::DOWN] = pOCGPoint[i+1];
			}
			else
			{
				OCGDir[(int)DIRECTION::UP] = pOCGPoint[i + 1];
				OCGDir[(int)DIRECTION::DOWN] = pOCGPoint[i];
			}
		}
		// << : BETWEEN POINT
	}
}
// << : Player On OCG

// >> : Finish OCG
bool CPlayer::IsClockwise()
{
	if (eDirStart == DIRECTION::DOWN)
	{
		if (eDirCrnt == DIRECTION::RIGHT)
		{
			if (pOCGPoint[0].y > pOCGPoint[ocgCnt - 1].y) return  true;
			else return  false;
		}
		else if (eDirCrnt == DIRECTION::LEFT)
		{
			if (pOCGPoint[0].y > pOCGPoint[ocgCnt - 1].y) return  false;
			else return  true;
		}
		else if (eDirCrnt == DIRECTION::UP)
		{
			if (pOCGPoint[0].x > pOCGPoint[ocgCnt - 1].x) return  true;
			else return  false;
		}
	}
	else if (eDirStart == DIRECTION::UP)
	{
		if (eDirCrnt == DIRECTION::RIGHT)
		{
			if (pOCGPoint[0].y > pOCGPoint[ocgCnt - 1].y) return  true;
			else return  false;

		}
		else if (eDirCrnt == DIRECTION::LEFT)
		{
			if (pOCGPoint[0].y > pOCGPoint[ocgCnt - 1].y) return  false;
			else return  true;
		}
		else if (eDirCrnt == DIRECTION::DOWN)
		{
			if (pOCGPoint[0].x > pOCGPoint[ocgCnt - 1].x) return  false;
			else return true;
		}
	}
	else if (eDirStart == DIRECTION::RIGHT)
	{
		if (eDirCrnt == DIRECTION::UP)
		{
			if (pOCGPoint[0].x > pOCGPoint[ocgCnt - 1].x) return  true;
			else return  false;
		}
		else if (eDirCrnt == DIRECTION::DOWN)
		{
			if (pOCGPoint[0].x > pOCGPoint[ocgCnt - 1].x) return  false;
			else return  true;
		}
		else if (eDirCrnt == DIRECTION::LEFT)
		{
			if (pOCGPoint[0].y > pOCGPoint[ocgCnt - 1].y) return  false;
			else return  true;
		}
	}
	else if (eDirStart == DIRECTION::LEFT)
	{
		if (eDirCrnt == DIRECTION::UP)
		{
			if (pOCGPoint[0].x > pOCGPoint[ocgCnt - 1].x) return true;
			else return false;
		}
		else if (eDirCrnt == DIRECTION::DOWN)
		{
			if (pOCGPoint[0].x > pOCGPoint[ocgCnt - 1].x) return false;
			else return true;
		}
		else if (eDirCrnt == DIRECTION::RIGHT)
		{
			if (pOCGPoint[0].y > pOCGPoint[ocgCnt - 1].y) return true;
			else return false;
		}
	}
	return false;
}

PackOCG CPlayer::GetOCGPack()
{
	bool bSameDir = eDirStart == eDirCrnt ? true : false;
	if (pOCGPoint[ocgCnt - 1] == Point(0, 0)) ocgCnt--;
	if (pOCGPoint[0] == Point(0, 0))
	{
		for (int i = 1; i < ocgCnt; i++)
		{
			pOCGPoint[i - 1] = pOCGPoint[i]; 
		}
	}
	return PackOCG(pOCGPoint, ocgCnt, IsClockwise(), eDirStart, bSameDir);
}

void CPlayer::GoBackOCG0()
{
	if (eState == PLAYER_STATE::GOBACK || eState == PLAYER_STATE::OCCUPYING)
	{
		vCenter = pOCGPoint[0].ToVec2();
		eState = PLAYER_STATE::ON_OCCUPIED;
		SetPosition(vCenter);
		pOCGPoint[0] = vCenter;
		ocgCnt = 0;
	}
	fStamina = 50;
	CScene* crntScene = CSceneMgr::GetInst()->GetCurrentScene();
	crntScene->PlayerLoseLife();
	pokemon->IncreaseUltimate();
}

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	if (_pOther->getOwnerObject()->getGroup() == GROUP_TYPE::PLAYER_DEBUFF)
	{
		bSwamp = true;
	}
}

void CPlayer::OnCollisionExit(CCollider* _pOther)
{
	if (_pOther->getOwnerObject()->getGroup() == GROUP_TYPE::PLAYER_DEBUFF)
	{
		bSwamp = false;
	}
}

// << : Finish OCG

void CPlayer::CreateMissile()
{
	Point crntPos = GetPosition();
	crntPos.y -= round((float)GetScale().y / 2);

	Point vecScale = { 10,10 };

	CMissile* newObj = new CMissile(crntPos, vecScale);
	newObj->set_Direction({ 0, -1 });
	newObj->SetSpeed(300);

	CreateObject(newObj, GROUP_TYPE::PLAYER_PROJECTILE);
}

OCDPoint* CPlayer::GetOCDVec2()
{
	CScene* crntScene = CSceneMgr::GetInst()->GetCurrentScene();

	return crntScene->GetOCD()->GetOCDCrnt();
}

void CPlayer::ConfigNxtPrv()
{
	OCDPoint* pOCD = GetOCDVec2();
	
	Point crntPos = GetPosition();
	OCDPoint* temp = pOCD;
	do
	{
		if (IsBetweenXorY(pOCD->pPoint, pOCD->nxt->pPoint, crntPos))
		{
			ocdPrv = pOCD;
			ocdNxt = pOCD->nxt;
		}
		pOCD = pOCD->nxt;
	} while (pOCD != temp);
}
void CPlayer::ConfigOCDDir()
{
	OCDPoint* ocdPoint= GetOCDVec2();
	OCDPoint* temp = ocdPoint;
	Point pCenter = vCenter.ToPoint();
	for (int i = 0; i < (int)DIRECTION::END; i++)
	{
		OCDDir[i] = nullptr;
	}
	do
	{
		// >> : ON POINT
		if (ocdPoint->pPoint==pCenter)
		{
			if (pCenter.x == ocdPoint->nxt->pPoint.x)
			{
				if (pCenter.y > ocdPoint->nxt->pPoint.y)
					OCDDir[(int)DIRECTION::UP] = ocdPoint->nxt;
				else OCDDir[(int)DIRECTION::DOWN] = ocdPoint->nxt;
			}
			else if (pCenter.y == ocdPoint->nxt->pPoint.y)
			{
				if (pCenter.x < ocdPoint->nxt->pPoint.x)
					OCDDir[(int)DIRECTION::RIGHT] = ocdPoint->nxt;
				else OCDDir[(int)DIRECTION::LEFT] = ocdPoint->nxt;
			}
			if (pCenter.x == ocdPoint->prv->pPoint.x)
			{
				if (pCenter.y > ocdPoint->prv->pPoint.y)
					OCDDir[(int)DIRECTION::UP] = ocdPoint->prv;
				else OCDDir[(int)DIRECTION::DOWN] = ocdPoint->prv;
			}
			else if (pCenter.y == ocdPoint->prv->pPoint.y)
			{
				if (pCenter.x < ocdPoint->prv->pPoint.x)
					OCDDir[(int)DIRECTION::RIGHT] = ocdPoint->prv;
				else OCDDir[(int)DIRECTION::LEFT] = ocdPoint->prv;
			}
		}
		// << : ON POINT
		// >> : BETWEEN POINT
		else if (IsBetweenX(ocdPoint->pPoint, ocdPoint->nxt->pPoint, pCenter))
		{
			Vec2 newVec1 = Vec2(ocdPoint->pPoint.x, ocdPoint->pPoint.y - 10);
			Vec2 newVec2 = Vec2(ocdPoint->pPoint.x, ocdPoint->pPoint.y + 10);
			if (IsBetweenY(newVec1, newVec2, pCenter))
			{
				if (pCenter.x > ocdPoint->pPoint.x)
				{
					OCDDir[(int)DIRECTION::LEFT] = ocdPoint;
					OCDDir[(int)DIRECTION::RIGHT] = ocdPoint->nxt;
				}
				else
				{
					OCDDir[(int)DIRECTION::LEFT] = ocdPoint->nxt;
					OCDDir[(int)DIRECTION::RIGHT] = ocdPoint;
				}
			}
		}
		else if (IsBetweenY(ocdPoint->pPoint, ocdPoint->nxt->pPoint, pCenter))
		{
			Vec2 newVec1 = Vec2(ocdPoint->pPoint.x-10, ocdPoint->pPoint.y);
			Vec2 newVec2 = Vec2(ocdPoint->pPoint.x + 10, ocdPoint->pPoint.y);
			if (IsBetweenX(newVec1, newVec2, pCenter))
			{
				if (pCenter.y >= ocdPoint->pPoint.y)
				{
					OCDDir[(int)DIRECTION::UP] = ocdPoint;
					OCDDir[(int)DIRECTION::DOWN] = ocdPoint->nxt;
				}
				else
				{
					OCDDir[(int)DIRECTION::UP] = ocdPoint->nxt;
					OCDDir[(int)DIRECTION::DOWN] = ocdPoint;
				}
			}
		}
		// << : BETWEEN POINT
		ocdPoint = ocdPoint->nxt;
	} while (ocdPoint != temp);
}


void CPlayer::PreventPlayerExceed()
{
	bool isNull = true;	
	if (OCDDir[(int)DIRECTION::UP] != nullptr)
	{
		if (pCenter.y < OCDDir[(int)DIRECTION::UP]->pPoint.y)
		{
			vCenter.y = OCDDir[(int)DIRECTION::UP]->pPoint.y;
			return;
		}
		isNull = false;
	}
	if (OCDDir[(int)DIRECTION::DOWN] != nullptr)
	{
		if (pCenter.y > OCDDir[(int)DIRECTION::DOWN]->pPoint.y)
		{
			vCenter.y = OCDDir[(int)DIRECTION::DOWN]->pPoint.y;
			return;
		}
		isNull = false;
	}
	if (OCDDir[(int)DIRECTION::RIGHT] != nullptr)
	{
		if (pCenter.x > OCDDir[(int)DIRECTION::RIGHT]->pPoint.x)
		{
			vCenter.x = OCDDir[(int)DIRECTION::RIGHT]->pPoint.x;
			return;
		}
		isNull = false;
	}
	if (OCDDir[(int)DIRECTION::LEFT] != nullptr)
	{
		if (pCenter.x < OCDDir[(int)DIRECTION::LEFT]->pPoint.x)
		{
			vCenter.x = OCDDir[(int)DIRECTION::LEFT]->pPoint.x;
			return;
		}
		isNull = false;
	}

	if (isNull&&eState==PLAYER_STATE::ON_OCCUPIED)
	{
		OCDPoint* ocdCrnt = GetOCDVec2();
		OCDPoint* temp = ocdCrnt;
		do
		{
			if (ocdCrnt->pPoint.AroundEqual(pCenter))
			{
				vCenter = ocdCrnt->pPoint.ToVec2();
				break;
			}
			ocdCrnt = ocdCrnt->nxt;
		} while (temp != ocdCrnt);
	}
}
bool CPlayer::IsPlayerOnOCD()
{
	/*
	pCenter = vCenter.ToPoint();
	OCDPoint* ocdCrnt = GetOCDVec2();
	OCDPoint* temp = ocdCrnt;
	do
	{
 		if (IsBetweenY(ocdCrnt->pPoint,ocdCrnt->nxt->pPoint, pCenter))
		{
			Vec2 newVec = Vec2(ocdCrnt->pPoint.x - 10, ocdCrnt->pPoint.y);
			Vec2 newVec2 = Vec2(ocdCrnt->pPoint.x + 10, ocdCrnt->pPoint.y);
			if (IsBetweenX(newVec, newVec2, pCenter))
			{
				if()
				vCenter = Vec2(ocdCrnt->pPoint.x, pCenter.y);
				return true;
			}
		}
		if (IsBetweenX(ocdCrnt->pPoint, ocdCrnt->nxt->pPoint, pCenter))
		{ 
			Vec2 newVec = Vec2(ocdCrnt->pPoint.x, ocdCrnt->pPoint.y-10);
			Vec2 newVec2 = Vec2(ocdCrnt->pPoint.x, ocdCrnt->pPoint.y+10);
			if (IsBetweenY(newVec, newVec2, pCenter))
			{
				vCenter = Vec2(pCenter.x, ocdCrnt->pPoint.y);
				return true;
			}
		}
		if (ocdCrnt->pPoint == pCenter)
			return true;
		ocdCrnt = ocdCrnt->nxt;
		
	} while (temp != ocdCrnt);


	for (int i = 0; i < (int)DIRECTION::END; i++)
	{
		if (OCDDir[i] == nullptr) continue;
		if (pCenter.x  == OCDDir[i]->pPoint.x) return true;
		else if (pCenter.y == OCDDir[i]->pPoint.y)return true;
	}
	return false;*/

	pCenter = vCenter.ToPoint();
	OCDPoint* ocdCrnt = GetOCDVec2();
	OCDPoint* temp = ocdCrnt;

	for (int i = 0; i < (int)DIRECTION::END; i++)
	{
		if (OCDDir[i] == nullptr) continue;
  		if (pCenter.x  == OCDDir[i]->pPoint.x)
			return true;
		else if (pCenter.y == OCDDir[i]->pPoint.y)
			return true;
	}
	return false;
}

bool CPlayer::IsPlayerOnOCG()
{
	return false;
}

bool CPlayer::IsOCGExceed(Point center)
{
 	for (int i = 0; i < ocgCnt; i++)
	{
		if(IsBetweenY(pOCGPoint[i], pOCGPoint[i + 1], center))
		{
			if (IsBetweenTwo(pOCGPoint[i].x - 10, pOCGPoint[i].x + 10, center.x))
			{
				return true;
			}
		}
		if (IsBetweenX(pOCGPoint[i], pOCGPoint[i + 1], center))
		{
			if (IsBetweenTwo(pOCGPoint[i].y - 10, pOCGPoint[i].y + 10, center.y))
			{
				return true;
			}
		}
	}

	return false;
}

void CPlayer::SetSpeed()
{
	float Swamp = 1;
	float Running = 1;
	float Retreat = 1;
	if (bSwamp)
		Swamp *= 0.5;
	if (bRunning)
		Running *= 2;
	if (bRetreat)
		Retreat *= 1.5;
	fTotalSpeed = fSpeed * Swamp * Running * Retreat * fDT;
}


DIRECTION CPlayer::OppositeDirection(DIRECTION _dir)
{
	switch (_dir)
	{
		case DIRECTION::UP:
			return DIRECTION::DOWN;
		case DIRECTION::DOWN:
			return DIRECTION::UP;
		case DIRECTION::RIGHT:
			return DIRECTION::LEFT;
		case DIRECTION::LEFT:
			return DIRECTION::RIGHT;
	}
}

void CPlayer::MoveUp()
{
	vCenter.y -= fTotalSpeed;
	eDirCrnt = DIRECTION::UP;
	moved = true;
}
void CPlayer::MoveDown()
{
	vCenter.y += fTotalSpeed;
	eDirCrnt = DIRECTION::DOWN;
	moved = true;
}
void CPlayer::MoveRight()
{
	vCenter.x += fTotalSpeed;
	eDirCrnt = DIRECTION::RIGHT;
	moved = true;
}
void CPlayer::MoveLeft()
{
	vCenter.x -= fTotalSpeed;
	eDirCrnt = DIRECTION::LEFT;
	moved = true;
}