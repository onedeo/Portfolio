#include "CScene_Start.h"
#include "pch.h"
#include "CObject.h"
#include "COcuppied.h"
#include "CCore.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CCollisionMgr.h"
#include "CSceneMgr.h"
#include "CResMgr.h"
#include "CSound.h"
#include "CCore.h"

class CObject;
class CPlayer;
class CEnemey;
class CUI;

void CScene_Start::Update()
{
	CScene::Update();
}

void CScene_Start::Enter()
{

		
	// >> : Create OCDPolygon
	COcuppied* pOCD = new COcuppied;
	pOCD->ResetToStart();

	SetOCD(pOCD);
	AddObject(pOCD, GROUP_TYPE::OCDPOLYGON);
	// << : Create OCDPolygon 

	// >> : Create Player
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetScale(Vec2(100.f, 100.f));
	pPlayer->ResetToStart();

	SetPlayer(pPlayer);
	AddObject(pPlayer, GROUP_TYPE::PLAYER);
	// << : Create Player
		
	// >> : Create Enemy
	float fEnemyScale = 50;

	CEnemy* pEnemy = new CEnemy;
	pEnemy->SetPosition(Vec2(0, 0));
	pEnemy->SetScale(Vec2(fEnemyScale));

	SetEnemy(pEnemy);
	AddObject(pEnemy, GROUP_TYPE::MONSTER);
	// << : Create Enemy

	// >> : Creat UI
	CUI* pUI = new CUI;
	SetUI(pUI);
	AddObject(pUI, GROUP_TYPE::UI);

	iLife = 3;
	iUltimate = 1;
	GetUI()->UpdateLife(iLife);
	GetUI()->UpdateUltimate(iUltimate);
	// << : Creat UI
	//충돌 지정
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_PROJECTILE, GROUP_TYPE::MONSTER_PROJECTILE);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_PROJECTILE, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER_DEBUFF, GROUP_TYPE::PLAYER);
}

void CScene_Start::Exit()
{
	DeleteAll();
	CCollisionMgr::GetInst()->ResetGroup();
}

void CScene_Start::PlayerLoseLife()
{
	iLife--;
	if (iLife < 0)
	{
		wstring strTag = L"MusicLose";
		wstring strPath = L"Sound\\" + strTag + L".wav";
		sndLose = CResMgr::GetInst()->LoadSound(strTag, strPath, false);
		sndLose->Load(strTag, false);
		Sleep(8000);

		CCore::GetInst()->SetCleared(false);
		ChangeScene(SCENE_TYPE::CLOSING); 
	}
	GetUI()->UpdateLife(iLife);
}

void CScene_Start::PokemonUseUltimate(int _ultimate)
{ 
	iUltimate = _ultimate;
	GetUI()->UpdateUltimate(_ultimate);
}

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
	CCollisionMgr::GetInst()->ResetGroup();
}
