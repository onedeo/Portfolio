#include <tchar.h>
#include "../Header/CPokemon.h"
#include "../Header/CResMgr.h"
#include "../Header/CRes.h"
#include "../Header/CPathMgr.h"
#include "../Header/CSceneMgr.h"
#include "../Header/CScene.h"
#include "../Header/CMissile.h"
#include "../Header/CKeyMgr.h"
#include"../Header/SelectGDI.h"

CPokemon::CPokemon()
{
	Init();
}

CPokemon::~CPokemon()
{
}

void CPokemon::Update()
{
	CScene* crntScene = CSceneMgr::GetInst()->GetCurrentScene();
	vPlayer = crntScene->GetPlayer()->GetPosition();
	eDirPlayer = crntScene->GetPlayer()->GetCrntDirection();
	fDTAccum += fDT;
	if (fBoltLeft >= 0)
		fBoltLeft -= fDT;
	if (fUltimateLeft >= 0)
		fUltimateLeft -= fDT;

	if (eState == STATE::FOLLOW)
	{
		if (GetDistance(vCenter, vPlayer) > 50.f)
			ComeBack();
	}

	if (eState == STATE::COME_BACK)
	{
		if (fDTAccum > 1)
		{
			ComeBack();
			if (GetDistance(vCenter, vPlayer) < 30.f)
				eState = STATE::FOLLOW;
		}
	}


	if(KEY_TAP(KEY::Q) && fBoltLeft < 0)
	{
		vCenTemp = vCenter;
		fDTAccum = 0;
		eState = STATE::USE_SKILL;
	}
	if (KEY_HOLD(KEY::Q)&&fBoltLeft<0&&eState==STATE::USE_SKILL)
	{
		PositionUsingSkill();
	}
	if (KEY_AWAY(KEY::Q) && fBoltLeft < 0 && eState == STATE::USE_SKILL)
	{
		if (fDTAccum > 5)
			iBoltQuant = 10;
		else
			iBoltQuant = ((int)fDTAccum+1)*2;
		ThunderBolt();
		eState = STATE::COME_BACK;
		fDTAccum = 0;
		fBoltLeft = iBoltCool;
	}

	if (KEY_TAP(KEY::R)&&iUltimate>0)
	{
		Ultimate();
		fUltimateLeft = iUltimateCool;
	}

	if (KEY_TAP(KEY::UP))
		eDirCrnt = DIRECTION::UP;
	if (KEY_TAP(KEY::DOWN))
		eDirCrnt = DIRECTION::DOWN;
	if (KEY_TAP(KEY::RIGHT))
		eDirCrnt = DIRECTION::RIGHT;
	if (KEY_TAP(KEY::LEFT))
		eDirCrnt = DIRECTION::LEFT;

	SetPosition(vCenter);
}

void CPokemon::Render(HDC _dc)
{
	SetScale(Vec2(pTex->getWidth(), pTex->getHeight()));
	vScale = GetScale();
	Point pDraw = vCenter.ToPoint();
	pDraw.x -= round((vScale.x) / 2);
	pDraw.y -= round((vScale.y) / 2);
	TransparentBlt(_dc, pDraw.x, pDraw.y, vScale.x, vScale.y, pTex->getDC(), 0, 0, vScale.x, vScale.y, RGB(255, 255, 255));

	RenderGage(_dc);
}

void CPokemon::RenderGage(HDC _dc)
{
	Point pStart = { vCenter.x - 30, vCenter.y - 35 };
	Point pYellow = { 60 * (1 - (fBoltLeft / iBoltCool)), 10 };

	RECT rectGage = { pStart.x, pStart.y,pStart.x + 60,pStart.y + 10 };
	RECT rectYellow = { pStart.x,pStart.y, pStart.x + pYellow.x,pStart.y + pYellow.y };
	Rectangle(_dc, rectGage.left, rectGage.top, rectGage.right, rectGage.bottom );
	SelectGDI brush(_dc, BRUSH_TYPE::YELLOW);
	Rectangle(_dc, rectYellow.left, rectYellow.top, rectYellow.right, rectYellow.bottom);
}

void CPokemon::IncreaseUltimate()
{
	if (iUltimate < 3)iUltimate++;
	CScene* crntScene = CSceneMgr::GetInst()->GetCurrentScene();
	crntScene->PokemonUseUltimate(iUltimate);
}


void CPokemon::FollowPosition()
{
	int radius = 40;

	if (GetDistance(vPlayer, vCenter) > radius)
	{
		vCenter = vPlayer;
		switch (eDirPlayer)
		{
			case DIRECTION::UP:
				vCenter.y += radius;
				vCenter.x += 15;
				break;
			case DIRECTION::DOWN:
				vCenter.y -= radius;
				vCenter.x += 15;
				break;
			case DIRECTION::RIGHT:
				vCenter.x -= radius;
				break;
			case DIRECTION::LEFT:
				vCenter.x += radius;
				break;
		}
	}
}

void CPokemon::ComeBack()
{
	vDir = Vec2(vPlayer.x - vCenter.x, vPlayer.y - vCenter.y);
	if (vDir.x != 0 && vDir.y != 0)
		vDir.Normalize();

	vCenter.x += fDT * fSpeedBack * vDir.x;
	vCenter.y += fDT * fSpeedBack * vDir.y;
}

void CPokemon::PositionUsingSkill()
{
	if (GetDistance(vPlayer, vCenter) > 100) return;
	switch (eDirCrnt)
	{
		case DIRECTION::UP:
			vCenter.y -= fSpeed * fDT;
			break;
		case DIRECTION::DOWN:
			vCenter.y += fSpeed * fDT;
			break;
		case DIRECTION::RIGHT:
			vCenter.x += fSpeed * fDT;
			break;
		case DIRECTION::LEFT:
			vCenter.x -= fSpeed * fDT;
			break;
	}
}

void CPokemon::Init()
{
	pTex = CResMgr::GetInst()->LoadTexture(L"PikachuIdle", L"Texture\\monster\\pikachu\\Pikachu_Idle.bmp");
	wstring strFilepath = CPathMgr::GetInst()->getContentPath();
	strFilepath += L"Texture\\monster\\pikachu\\Pikachu_Idle.bmp";

	pTex->Load(strFilepath);

	
	fSpeed = 100;
	fSpeedBack = 200;
	eState = STATE::FOLLOW;

	iBoltCool = 3;
	fBoltLeft = 0;
	iUltimateCool = 0;
	fUltimateLeft = 0;
	iUltimate = 1;
}

void CPokemon::ThunderBolt()
{
	for (int i = 0; i < iBoltQuant; i++)
	{
		Vec2 vVectorTo = Vec2(rand() % 200 - 100, rand() % 200 - 100);
		float speed = rand() % 30 + 40;
		CreateThunderBolt(vVectorTo, speed);
	}
}

void CPokemon::CreateThunderBolt(Vec2 _dir, float _fspeed)
{
	CMissile* pMissile = new CMissile();
	pMissile->SetPosition(vCenter);
	pMissile->InitThunderBolt(_dir, _fspeed);

	CreateObject(pMissile, GROUP_TYPE::PLAYER_PROJECTILE);
}

void CPokemon::Ultimate()
{
	CMissile* pMissile = new CMissile();

	bool bDoOnce = false;
	for (int i = 0; i < 100; i++)
	{
		pMissile = new CMissile();
		pMissile->PikachuUltimate(vCenter);
		CreateObject(pMissile, GROUP_TYPE::PLAYER_PROJECTILE);
	}
	iUltimate--;
	CScene* crntScene = CSceneMgr::GetInst()->GetCurrentScene();
	crntScene->PokemonUseUltimate(iUltimate);
}
