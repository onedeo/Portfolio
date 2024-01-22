#include <tchar.h>
#include "COcuppied.h"
#include "CCore.h";
#include "CSceneMgr.h"
#include "CScene.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "SelectGDI.h"
#include "CKeyMgr.h"
#include "CMonster_Sub.h"
#include "CSound.h"

COcuppied::COcuppied()
	:ocdAddStart(nullptr)
	,ocdDeleteStart(nullptr)
	,ocdDeleteEnd(nullptr)
	,Sannabi(false)
{
}

COcuppied::~COcuppied()
{
	//Delete all OCD to reset
}
void COcuppied::Update()
{
	if (KEY_HOLD(KEY::W) && KEY_HOLD(KEY::E))
	{
		FinishRatio = 0;
	}

	if (bFinishGame)
	{
		fDTCatch += fDT;
		bool bCatch = false;
		if (GetDistance(vBallCenter, vEnemyCen) < 50||(fDTCatch>2&&GetDistance(vBallCenter, vEnemyCen) < 200))
		{
			bCatch = true;
		}

		CScene* crntScene = CSceneMgr::GetInst()->GetCurrentScene();
		Point vEnemyCen = crntScene->GetEnemy()->GetPosition();
		vBallDir = Vec2(vEnemyCen.x - vBallCenter.x, vEnemyCen.y - vBallCenter.y);
		vBallDir.Normalize();

		vBallCenter.x += vBallDir.x * fDT * fBallSpeed;
		vBallCenter.y += vBallDir.y * fDT * fBallSpeed;
		if (bCatch)
		{
			FinishGame();
		}
	}
}

void COcuppied::Render(HDC _dc)
{
	OCDPoint* tempvec = ocdVec2;
	POINT ocdpoint[500];
	int ocdcount = 0;
	do
	{
		ocdpoint[ocdcount].x = ocdVec2->pPoint.x;
		ocdpoint[ocdcount++].y = ocdVec2->pPoint.y;
		ocdVec2 = ocdVec2->nxt;
	} while (tempvec != ocdVec2);
	HRGN hPolygonRgn = CreatePolygonRgn(ocdpoint, ocdcount, WINDING);
	HBRUSH hPolygonBrush = CreatePatternBrush(hBit);
	FillRgn(_dc, hPolygonRgn, hPolygonBrush);
	DeleteObject(hPolygonRgn);
	DeleteObject(hPolygonBrush);
	DeleteObject(hBit);
	// << : OCD Transparent

	// >> : Total Image
	OCDPoint* temp = ocdVec2;
	TCHAR point[20];
	int count = 0;
	//if (KEY_TAP(KEY::TAB))
	//	bShowDebug = !bShowDebug;
	do
	{
		if (bShowDebug)
		{
			_stprintf_s(point, _T("OCD[%d]:(%d, %d)"), count, ocdVec2->pPoint.x, ocdVec2->pPoint.y);
			TextOut(_dc, ocdVec2->pPoint.x - 50, ocdVec2->pPoint.y, point, _tcslen(point));
			count++;
		}
		MoveToEx(_dc, ocdVec2->pPoint.x, ocdVec2->pPoint.y, NULL);
		ocdVec2 = ocdVec2->nxt;
		LineTo(_dc, ocdVec2->pPoint.x, ocdVec2->pPoint.y);
	} while (ocdVec2 != temp);
	// << : Total Image

	if (bFinishGame)
	{
		TransparentBlt(_dc, vBallCenter.x-pBallScale.x/2, vBallCenter.y- pBallScale.y/2, pBallScale.x, pBallScale.y, texBall->getDC(), 0,0,pBallScale.x, pBallScale.y, RGB(255, 0, 255));
	}
}

void COcuppied::UpdateOCDArea()
{
	OCDPoint* temp = ocdVec2;
	float fSum1 = 0;
	float fSum2 = 0;
	do
	{
		fSum1 += ocdVec2->pPoint.x * ocdVec2->nxt->pPoint.y;
		fSum2 += ocdVec2->pPoint.y * ocdVec2->nxt->pPoint.x;
		ocdVec2 = ocdVec2->nxt;
	} while (ocdVec2 != temp);
	fOCDArea = (fSum1 - fSum2) / 2;

	fTotalPercent = (fTotalArea - fOCDArea) / fTotalArea;
}

void COcuppied::ResetToStart()
{
	//stage1 bulbasour
	// >> : Load Image
	//BG
	texBG = CResMgr::GetInst()->LoadTexture(L"BulbasourBG", L"Texture\\monster\\bulbasaur\\background\\bulbasourBG.bmp");
	wstring strFilepath = CPathMgr::GetInst()->getContentPath();
	strFilepath += L"Texture\\monster\\bulbasaur\\background\\bulbasourBG.bmp";
	hBit = texBG->Load(strFilepath);
	//OCD
	texOCD = CResMgr::GetInst()->LoadTexture(L"BulbasourOCD", L"Texture\\monster\\bulbasaur\\background\\bulbasourOCD.bmp");
	strFilepath = CPathMgr::GetInst()->getContentPath();
	strFilepath += L"Texture\\monster\\bulbasaur\\background\\bulbasourOCD.bmp";
	texOCD->Load(strFilepath);
	//BALL
	texBall= CResMgr::GetInst()->LoadTexture(L"Ball", L"Texture\\OCD\\Ball.bmp");
	strFilepath = CPathMgr::GetInst()->getContentPath();
	strFilepath += L"Texture\\OCD\\Ball.bmp";
	vBallCenter = Vec2(0, 0);	
	pBallScale = Vec2(texBall->getWidth(), texBall->getHeight());
	// << : Load Image




	RECT rect = CCore::GetInst()->GetOCDTotalSize();

	OCDPoint* temp = new OCDPoint(Vec2(rect.left, rect.top));

	fTotalArea = (rect.right - rect.left) * (rect.bottom - rect.top);

	// >> : set head
	ocdVec2 = temp;
	ocdVec2->nxt = ocdVec2;
	ocdVec2->prv = ocdVec2;
	// << : set head

	// >> : insert basis points
	ocdVec2->InsertNxt(Vec2(rect.right, rect.top));
	ocdVec2 = ocdVec2->nxt;
	ocdVec2->InsertNxt(Vec2(rect.right, rect.bottom));
	ocdVec2 = ocdVec2->nxt;
	ocdVec2->InsertNxt(Vec2(rect.left, rect.bottom));
	// << : insert basis points

	CMonster_Sub* pMS = new CMonster_Sub();
	CreateObject(pMS, GROUP_TYPE::MONSTER_SUB);

	UpdateOCDArea();
	
	bFinishGame = false;
	fBallSpeed = 400;
	FinishRatio = 0.8;
}

void COcuppied::FinishGame()
{
	wstring strTag = L"MusicWin";
	wstring strPath = L"Sound\\" + strTag + L".wav";
	sndWin = CResMgr::GetInst()->LoadSound(strTag, strPath, false);
	sndWin->Load(strTag, false);
	Sleep(5000);

	CCore::GetInst()->SetCleared(true);
	ChangeScene(SCENE_TYPE::CLOSING);
}

void COcuppied::FinishOCG(PackOCG _ocgPack)
{
	ocgPack = _ocgPack;
	CScene* crntScene = CSceneMgr::GetInst()->GetCurrentScene();
	vEnemyCen = crntScene->GetEnemy()->GetPosition();
	
	if(!ocgPack.bSameDir)
	{
		if (!IsEnemyInOCG())
			ocgPack.bClockwise = !ocgPack.bClockwise;
		ConfigDeletePoint();
	}
	else
	{
		OCGSameDirection();
	}
	if (ocdDeleteStart == nullptr || ocdDeleteEnd == nullptr || ocdAddStart == nullptr) return;

	DeleteOCDPoint();
	AddOCGPoint();	

	bStartOCGonOCD = false;
	bEndOCGonOCD = false;

	StraightOCD();
	UpdateOCDArea();
	if (fTotalPercent> FinishRatio)
	{
		bFinishGame = true;
		fDTFinishGame = 0;
	}
}

bool COcuppied::IsEnemyInOCG()
{
	int enemyLineCnt = 0;

	//몬스터 좌우위아래 중 ocg 선이 홀수면 in 짝수면 out
	DIRECTION startCnt = DIRECTION::END;
	for (int i = 0; i < ocgPack.ocgCnt; i++)
	{
		if ((startCnt == DIRECTION::END || startCnt == DIRECTION::RIGHT) && vEnemyCen.x < ocgPack.ocgPoint[i].x)
		{
			if (IsBetweenY(ocgPack.ocgPoint[i], ocgPack.ocgPoint[(i + 1)%ocgPack.ocgCnt], vEnemyCen))
			{
				enemyLineCnt++;
				startCnt = DIRECTION::RIGHT;
			}
		}
		if ((startCnt == DIRECTION::END || startCnt == DIRECTION::LEFT) && vEnemyCen.x > ocgPack.ocgPoint[i].x)
		{
			if (IsBetweenY(ocgPack.ocgPoint[i], ocgPack.ocgPoint[(i + 1) % ocgPack.ocgCnt], vEnemyCen))
			{
				enemyLineCnt++;
				startCnt = DIRECTION::LEFT;
			}
		}
		if ((startCnt == DIRECTION::END || startCnt == DIRECTION::DOWN) && vEnemyCen.y < ocgPack.ocgPoint[i].y)
		{
			if (IsBetweenX(ocgPack.ocgPoint[i], ocgPack.ocgPoint[(i + 1) % ocgPack.ocgCnt], vEnemyCen))
			{
				enemyLineCnt++;
				startCnt = DIRECTION::DOWN;
			}
		}
		if ((startCnt == DIRECTION::END|| startCnt == DIRECTION::UP) && vEnemyCen.y > ocgPack.ocgPoint[i].y)
		{
			if (IsBetweenX(ocgPack.ocgPoint[i], ocgPack.ocgPoint[(i + 1) % ocgPack.ocgCnt], vEnemyCen))
			{
				enemyLineCnt++;
				startCnt = DIRECTION::UP;
			}
		}
	}
	if (enemyLineCnt % 2 != 0)
	{
		return true;
	}
	return false;
}

void COcuppied::ConfigDeletePoint()
{
	ocdDeleteStart = nullptr;
	ocdDeleteEnd = nullptr;
	ocdAddStart = nullptr;
	OCDPoint* temp = ocdVec2;
	if (ocgPack.bClockwise)
	{
		do
		{
			if (IsOnXorYAxis(ocdVec2->pPoint, ocdVec2->nxt->pPoint, ocgPack.ocgPoint[0])
				&&ocdDeleteStart==nullptr)
				//|| ocdVec2->pPoint.AroundEqual(ocgPack.ocgPoint[0]))
			{
				ocdDeleteStart = ocdVec2->nxt;
				ocdAddStart = ocdVec2;
			}
			if (IsOnXorYAxis(ocdVec2->pPoint, ocdVec2->nxt->pPoint, ocgPack.ocgPoint[ocgPack.ocgCnt - 1]))
				//|| ocdVec2->pPoint.AroundEqual(ocgPack.ocgPoint[ocgPack.ocgCnt - 1]))
			{
				ocdDeleteEnd = ocdVec2;
			}
			if (ocdVec2->pPoint.AroundEqual(ocgPack.ocgPoint[0]))
			{
				ocdDeleteStart = ocdVec2;
				ocdAddStart = ocdVec2->prv;
			}
			ocdVec2 = ocdVec2->nxt;
		} while (temp != ocdVec2);
	}
	else //ocgPack.bClockwise == true
	{
		do
		{
			if (IsOnXorYAxis(ocdVec2->pPoint, ocdVec2->nxt->pPoint, ocgPack.ocgPoint[0])
				&&ocdDeleteStart==nullptr)
				//|| ocdVec2->pPoint.AroundEqual(ocgPack.ocgPoint[0]))
			{
				ocdDeleteStart = ocdVec2;
				ocdAddStart = ocdVec2->nxt;
			}
			if (IsOnXorYAxis(ocdVec2->pPoint, ocdVec2->nxt->pPoint, ocgPack.ocgPoint[ocgPack.ocgCnt - 1]))
				//|| ocdVec2->pPoint.AroundEqual(ocgPack.ocgPoint[ocgPack.ocgCnt - 1]))
			{
				ocdDeleteEnd = ocdVec2->nxt;
			}
			if (ocdVec2->pPoint.AroundEqual(ocgPack.ocgPoint[0]))
			{
				ocdDeleteStart = ocdVec2->prv;
				ocdAddStart = ocdVec2;
			}
			ocdVec2 = ocdVec2->nxt;
		} while (temp != ocdVec2);
	}
}

void COcuppied::OCGSameDirection()
{
	OCDPoint* startPrv = nullptr;
	OCDPoint* startNxt = nullptr;

	OCDPoint* endPrv = nullptr;
	OCDPoint* endNxt = nullptr;

	/*
	끝점의 후점부터 시작점의 전점까지 하나의 다각형으로 보고 거기에 EnemyIn 여부 판단
	*/

	OCDPoint* ocdEnd = ocdVec2;
	do
	{
		//시작점의 전점과 후점
		if(IsOnXorYAxis(ocdVec2->pPoint, ocdVec2->nxt->pPoint, ocgPack.ocgPoint[0]))
		{
			startPrv = ocdVec2;
			startNxt = ocdVec2->nxt;
		}
		//끝점의 전점과 후점
		if (IsOnXorYAxis(ocdVec2->pPoint, ocdVec2->nxt->pPoint, ocgPack.ocgPoint[ocgPack.ocgCnt - 1]))
		{
			endPrv = ocdVec2;
			endNxt = ocdVec2->nxt;
		}
		ocdVec2 = ocdVec2->nxt;
	} while (ocdVec2 != ocdEnd);

	if (startPrv == nullptr || startNxt == nullptr || endPrv == nullptr || endNxt == nullptr) return;

	//끝점의 후점부터 시작의 전점을 추가하여 EnemyIn 판단
	int originalOCGCnt = ocgPack.ocgCnt;
	ocdVec2 = endNxt;
	while (ocdVec2 != startNxt)
	{
		ocgPack.ocgPoint[ocgPack.ocgCnt++] = ocdVec2->pPoint;
		ocdVec2 = ocdVec2->nxt;
	}
	bool bEnemeyIn = IsEnemyInOCG();
	ocgPack.ocgCnt = originalOCGCnt;

	ocdDeleteStart = nullptr;
	ocdDeleteEnd = nullptr;
	ocdAddStart = nullptr;

	if (ocgPack.dirStart == DIRECTION::UP || ocgPack.dirStart == DIRECTION::RIGHT)
	{
		if (bEnemeyIn)
		{
			ocdDeleteStart = startNxt;
			ocdDeleteEnd = endPrv;
			ocdAddStart = startPrv;
			ocgPack.bClockwise = true;
		}
		else
		{
			ocdDeleteStart = startPrv;
			ocdDeleteEnd = endNxt;
			ocdAddStart = startNxt;
			ocgPack.bClockwise = false;
		}
	}
	else 	if (ocgPack.dirStart == DIRECTION::DOWN || ocgPack.dirStart == DIRECTION::LEFT)
	{
		if (bEnemeyIn)
		{
			ocdDeleteStart = startNxt;
			ocdDeleteEnd = endPrv;
			ocdAddStart = startPrv;
			ocgPack.bClockwise = true;
		}
		else
		{
			ocdDeleteStart = startPrv;
			ocdDeleteEnd = endNxt;
			ocdAddStart = startNxt;
			ocgPack.bClockwise = false;
		}
	}
}

void COcuppied::DeleteOCDPoint()
{
	OCDPoint* temp = ocdDeleteStart;
	//시작점과 끝점 사이에 아무 점이 없고 몬스터가 안에 없을 때
	if (ocdDeleteStart == ocdDeleteEnd&&!ocdDeleteStart->pPoint.AroundEqual(ocdDeleteEnd->pPoint))
	{
		ocdDeleteStart->DeleteSelf();
		ocdDeleteStart = nullptr;
	}
	//시작점과 끝점 사이에 아무 점이 없고 몬스터가 안에 있을 때
	else if (IsEnemyInOCG()&&(ocdDeleteStart == ocdAddStart || ocdDeleteEnd == ocdAddStart))
	{
		if(ocgPack.bClockwise)
		{
			while (temp != ocdDeleteEnd)
			{
				temp = ocdDeleteStart->nxt;
				ocdDeleteStart->DeleteSelf();
				ocdDeleteStart = temp;
			}
			ocdDeleteEnd->DeleteSelf();
		}
		else //ocgPack.bClockwise==false;
		{
			while (temp != ocdDeleteEnd)
			{
				temp = ocdDeleteStart->prv;
				ocdDeleteStart->DeleteSelf();
				ocdDeleteStart = temp;
			}
			ocdDeleteEnd->DeleteSelf();
		}

		Sannabi = true;
	}
	else if (ocgPack.bClockwise)
	{
		OCDPoint* ocdEndNxt = ocdDeleteEnd->nxt;
		while(temp!=ocdEndNxt)
		{
			temp = temp -> nxt; 
			ocdDeleteStart->DeleteSelf();
			ocdDeleteStart = temp;
		}
	} 
	else //ocgPack.bClockwise==false
	{
		OCDPoint* ocdEndPrv = ocdDeleteEnd->prv;
		while (temp != ocdEndPrv)
		{

			temp = temp->prv;
			ocdDeleteStart->DeleteSelf();
			ocdDeleteStart = temp;
		}
	}
}
void COcuppied::AddOCGPoint()
{
	int i = 0;

	if (bStartOCGonOCD) i = 1;
	if (bEndOCGonOCD) ocgPack.ocgCnt--;
	if (!Sannabi)
	{
		if (ocgPack.bClockwise)
		{
			for (; i < ocgPack.ocgCnt; i++)
			{
				ocdAddStart->InsertNxt(ocgPack.ocgPoint[i].ToVec2());
				ocdAddStart = ocdAddStart->nxt;
			}
		}
		else //ocg.PackbClockwise==false
		{
			for (; i < ocgPack.ocgCnt; i++)
			{
				ocdAddStart->InsertPrv(ocgPack.ocgPoint[i].ToVec2());
				ocdAddStart = ocdAddStart->prv;
			}
		}
		ocdVec2 = ocdAddStart;
	}
	else
	{
		ocdVec2= new OCDPoint(ocgPack.ocgPoint[2]);
		ocdVec2->prv = new OCDPoint(ocgPack.ocgPoint[1]);
		ocdVec2->nxt = ocdVec2->prv;
		ocdVec2->prv->prv = ocdVec2;
		ocdVec2->prv->nxt = ocdVec2;

		ocdVec2->InsertNxt(ocgPack.ocgPoint[0]);
		
		for (int i = 3; i < ocgPack.ocgCnt; i++)
		{
			ocdVec2->InsertNxt(ocgPack.ocgPoint[i].ToVec2());
			ocdVec2 = ocdVec2->nxt;
		}

		Sannabi = false;
	}
}

void COcuppied::IsOnOCDPoint()
{
	OCDPoint* temp = ocdVec2;
	OCDPoint* temp2 = nullptr;
	OCDPoint* overlapPoint = nullptr;
	OCDPoint* changePoint = nullptr;
	bool isYaxis;
	do
	{
		if (ocgPack.ocgPoint[0].AroundEqual(ocdVec2->pPoint))
		{
			bStartOCGonOCD = true;
			//check axis
			if (ocgPack.dirStart == DIRECTION::UP || ocgPack.dirStart == DIRECTION::DOWN)
			{
				isYaxis = true;
			}
			else //DIRECTION RIGHT / LEFT
			{
				isYaxis = false;
			}

			if (isYaxis)
			{
				if (ocdVec2->prv->pPoint.y == ocdVec2->pPoint.y)
				{
					changePoint = ocdVec2->prv;
				}
				else
				{
					changePoint = ocdVec2->nxt;
				}
			}
			else
			{
				if (ocdVec2->prv->pPoint.x == ocdVec2->pPoint.x)
				{
					changePoint = ocdVec2->prv;
				}
				else
				{
					changePoint = ocdVec2->nxt;
				}
			}
			if (ocdDeleteStart == ocdVec2)
			{
				ocdDeleteStart = changePoint;
			}
			if (ocdDeleteEnd == ocdVec2)
			{
				ocdDeleteEnd = changePoint;
			}
			if (ocdAddStart == ocdVec2)
			{
				ocdAddStart = changePoint;
			}
			temp2 = ocdVec2;
			ocdVec2 = ocdVec2->nxt;
			temp2->DeleteSelf();
		}
		else if (ocgPack.ocgPoint[ocgPack.ocgCnt - 1].AroundEqual(ocdVec2->pPoint))
		{
			bEndOCGonOCD = true;
			//check axis
			if (ocgPack.dirStart == DIRECTION::UP || ocgPack.dirStart == DIRECTION::DOWN)
			{
				isYaxis = true;
			}
			else //DIRECTION RIGHT / LEFT
			{
				isYaxis = false;
			}

			if (isYaxis)
			{
				if (ocdVec2->prv->pPoint.y == ocdVec2->pPoint.y)
				{
					changePoint = ocdVec2->prv;
				}
				else
				{
					changePoint = ocdVec2->nxt;
				}
			}
			else
			{
				if (ocdVec2->prv->pPoint.x == ocdVec2->pPoint.x)
				{
					changePoint = ocdVec2->prv;
				}
				else
				{
					changePoint = ocdVec2->nxt;
				}
			}
			if (ocdDeleteStart == ocdVec2)
			{
				ocdDeleteStart = changePoint;
			}
			if (ocdDeleteEnd == ocdVec2)
			{
				ocdDeleteEnd = changePoint;
			}
			if (ocdAddStart == ocdVec2)
			{
				ocdAddStart = changePoint;
			}
			temp2 = ocdVec2;
			ocdVec2 = ocdVec2->nxt;
			temp2->DeleteSelf();
		}
		else ocdVec2 = ocdVec2->nxt;

	} while (temp != ocdVec2);
}

void COcuppied::StraightOCD()
{
	OCDPoint* temp = ocdVec2;
	bool bYAxis = false;
	if (abs(ocdVec2->pPoint.x - ocdVec2->nxt->pPoint.x) <= 1)
		bYAxis = true;
	do
	{
		if (bYAxis)
		{
			if (ocdVec2->pPoint.x != ocdVec2->nxt->pPoint.x)
				ocdVec2->pPoint.x = ocdVec2->nxt->pPoint.x;
		}
		else
		{
			if (ocdVec2->pPoint.y != ocdVec2->nxt->pPoint.y)
				ocdVec2->pPoint.y = ocdVec2->nxt->pPoint.y;
		}
		bYAxis = !bYAxis;
		ocdVec2 = ocdVec2->nxt;
	} while (ocdVec2 != temp);

	temp = ocdVec2;
	do
	{
		if (ocdVec2->pPoint == ocdVec2->nxt->pPoint)
		{
			if (temp == ocdVec2->nxt)
				temp = temp->nxt;
			ocdVec2->nxt->DeleteSelf();
		}
		else ocdVec2 = ocdVec2->nxt;
	} while (temp != ocdVec2);
}
