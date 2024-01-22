#include "tchar.h"
#include "CMonster_Sub.h"
#include "CRes.h"
#include "CResMgr.h"
#include "CCollider.h"
#include "CMissile.h"



CMonster_Sub::CMonster_Sub()
{
	Init();
}

CMonster_Sub::~CMonster_Sub()
{
}

void CMonster_Sub::Render(HDC _dc)
{
	Point pCenter = vCenter.ToPoint();
	Point pScale = vScale.ToPoint();
	if (eState == STATE_MS::LEAF)
	{
		TransparentBlt(_dc, pCenter.x, pCenter.y, pScale.x, pScale.y, texTreeFull->getDC(), 0, 0, pScale.x, pScale.y, RGB(255, 0, 255));
	}
	else if (eState == STATE_MS::EMPTY)
	{
		TransparentBlt(_dc, pCenter.x, pCenter.y, pScale.x, pScale.y, texTreeEmpty->getDC(), 0, 0, pScale.x, pScale.y, RGB(255, 0, 255));
	}
}

void CMonster_Sub::Update()
{
	if (fDT < 1)
		fDTAccum += fDT;
	if (fDTAccum > 5)
	{
		eState = STATE_MS::LEAF;
	}
	if (fDTAccum > 10)
	{
		eState = STATE_MS::EMPTY;
		CreateRazorLeaf();
		fDTAccum = 0;
	}
}

void CMonster_Sub::Init()
{
	eState = STATE_MS::EMPTY;

	texTreeFull = CResMgr::GetInst()->LoadTexture(L"TreeFull", L"Texture\\monster\\bulbasaur\\TreeFull.bmp");
	wstring strFilePath = texTreeFull->getRelativePath();
	strFilePath += L"Texture\\monster\\bulbasaur\\TreeFull.bmp";
	texTreeFull->setRelativePath(strFilePath);

	texTreeEmpty = CResMgr::GetInst()->LoadTexture(L"TreeEmpty", L"Texture\\monster\\bulbasaur\\TreeEmpty.bmp");
	strFilePath = texTreeEmpty->getRelativePath();
	strFilePath += L"Texture\\monster\\bulbasaur\\Treel.bmp";
	texTreeEmpty->setRelativePath(strFilePath);


	setGroup(GROUP_TYPE::MONSTER_SUB);
	vScale = Vec2(texTreeFull->getWidth(), texTreeFull->getHeight());
	SetScale(vScale);


	vCenter = Vec2(900, (int)(668-vScale.y));
	SetPosition(vCenter);

	CreateCollider();
	getCollider()->setScale(vScale);
	getCollider()->setOffsetPos(Vec2(vScale.x / 2, vScale.y / 2));
}

void CMonster_Sub::CreateRazorLeaf()
{
	Vec2 vVectorTo;
	for (int i = 0; i < 20; i++)
	{
		vVectorTo = Vec2(rand() % 200 - 100, rand() % 200 - 100);
		CreateLeaf(vVectorTo, 10);
	}
}

void CMonster_Sub::CreateLeaf(Vec2 _dir, float _fspeed)
{
	//씬 가져오기
	//CScene* pCurrentScene = CSceneMgr::GetInst()->GetCurrentScene();

	//미사일 생성 시간 설정

	Vec2 vRePosition = GetPosition();
	vRePosition.x += vScale.x / 2-25;
	vRePosition.y += vScale.y / 2-80;

	CMissile* pMissile = new CMissile();
	pMissile->SetPosition(vRePosition);
	pMissile->InitLeaf1(_dir, _fspeed);

	CreateObject(pMissile, GROUP_TYPE::MONSTER_PROJECTILE);
}
