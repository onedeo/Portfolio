#include <tchar.h>
#include "../Header/CMissile.h"
#include "../Header/CCollider.h"
#include "../Header/CResMgr.h"
#include "../Header/CTexture.h"
#include "../Header/CScene.h"
#include "../Header/CSceneMgr.h"

static int UltiCnt;

void CMissile::Update()
{
	vCenter = GetPosition();
	if (fDT < 1)
		fDTAccum += fDT;
	if (eType == MISSILE_TYPE::LAZORLEAFT)
	{
		UpdateRazorLeaft();
	}
	else if (eType == MISSILE_TYPE::THUNDERBOLT)
	{
		UpdateThunderBolt();
	}
	else if (eType == MISSILE_TYPE::PIKACHU_ULTIMATE)
	{
		UpdatePikaUlti();
	}
	else if (eType == MISSILE_TYPE::SWAMP)
	{
		UpdateSwamp();
	}
	SetPosition(vCenter);
}

void CMissile::UpdateRazorLeaft()
{
	if (fDTAccum > 2 && iSkillNum == 1)
	{
		fSpeed = 100;
		iSkillNum = 0;
	}
	for (int i = 0; i < 7; i++)
	{
		vCenter.x += fDT * fSpeed * vDir.x;
		vCenter.y += fDT * fSpeed * vDir.y;
	}

	HitOCG();
	

	if (fDTAccum > 4)
	{
		myDeleteObject(this, GROUP_TYPE::PLAYER_PROJECTILE);
	}
}

void CMissile::UpdateThunderBolt()
{
	vCenter.x += fDT * fSpeed * vDir.x;
	vCenter.y += fDT * fSpeed * vDir.y;
	if (fDTAccum > 10) myDeleteObject(this, GROUP_TYPE::PLAYER_PROJECTILE);
}

void CMissile::UpdatePikaUlti()
{
	vCenter.x += fDT * fSpeed * vDir.x;
	vCenter.y += fDT * fSpeed * vDir.y;
	if (fDTAccum > 3) myDeleteObject(this, GROUP_TYPE::PLAYER_PROJECTILE);
}

void CMissile::UpdateSwamp()
{
	if (fDTAccum > 5) myDeleteObject(this, GROUP_TYPE::PLAYER_DEBUFF);
}


void CMissile::Render(HDC _dc)
{
	if (eType == MISSILE_TYPE::LAZORLEAFT)
	{
		RenderRazorLeaft(_dc);
	}
	else if (eType == MISSILE_TYPE::THUNDERBOLT)
	{
		RenderThunderBolt(_dc);
	}
	else if (eType == MISSILE_TYPE::PIKACHU_ULTIMATE)
	{
		RenderPikaUlti(_dc);
	}
	else if (eType == MISSILE_TYPE::SWAMP)
	{
		RenderSwamp(_dc);
	}
	ComponentRender(_dc);
}

void CMissile::RenderRazorLeaft(HDC _dc)
{
	Point pCenter = GetPosition();
	Point pScale = GetScale();
	TransparentBlt(_dc, pCenter.x, pCenter.y, pScale.x, pScale.y, texLeaf1->getDC(), 0, 0, pScale.x, pScale.y, RGB(121, 114, 121));
}

void CMissile::RenderThunderBolt(HDC _dc)
{
	Point pCenter = GetPosition();
	Point pScale = GetScale();
	TransparentBlt(_dc, pCenter.x, pCenter.y, pScale.x, pScale.y, texBolt->getDC(), 0, 0, pScale.x, pScale.y, RGB(255, 0, 255));
}

void CMissile::RenderPikaUlti(HDC _dc)
{
	Point pCenter = GetPosition();
	Point pScale = GetScale();
	TransparentBlt(_dc, pCenter.x, pCenter.y, pScale.x, pScale.y, texPikaUlti[iUltimateNum]->getDC(), 0, 0, pScale.x, pScale.y, RGB(255, 0, 255));
}

void CMissile::RenderSwamp(HDC _dc)
{
	Point pCenter = GetPosition();
	Point pScale = GetScale();
	pCenter.x -= pScale.x / 2;
	pCenter.y -= pScale.y / 2;

	TransparentBlt(_dc, pCenter.x, pCenter.y, pScale.x, pScale.y, texSwamp->getDC(), 0, 0, pScale.x, pScale.y, RGB(255, 0, 255));
}

void CMissile::InitLeaf1(Vec2 _dir, float _fspeed)
{
	texLeaf1 = CResMgr::GetInst()->LoadTexture(L"Leaf1", L"Texture\\monster\\bulbasaur\\leafs.bmp");
	wstring strFilePath = texLeaf1->getRelativePath();
	strFilePath += L"Texture\\monster\\bulbasaur\\leafs.bmp";
	setGroup(GROUP_TYPE::MONSTER_PROJECTILE);
	texLeaf1->setRelativePath(strFilePath);

	Vec2 vScale = { texLeaf1->getWidth(), texLeaf1->getHeight() };
	SetScale(vScale);

	CreateCollider();
	//getCollider()->setOffsetPos(vScale/2);
	Vec2 vColScale = vScale * 0.5;
	getCollider()->setScale(vColScale);
	getCollider()->setOffsetPos(vColScale);


	vDir = _dir;
	vDir.Normalize();

	fSpeed = _fspeed;
	iSkillNum = 1;
	fDTAccum = 0;
	eType = MISSILE_TYPE::LAZORLEAFT;
}

void CMissile::InitThunderBolt(Vec2 _dir, float _fspeed)
{
	texBolt = CResMgr::GetInst()->LoadTexture(L"ThunderBolt", L"Texture\\monster\\pikachu\\ThunderBolt.bmp");
	wstring strFilePath = texBolt->getRelativePath();
	strFilePath += L"Texture\\monster\\pikachu\\ThunderBolt.bmp";
	setGroup(GROUP_TYPE::PLAYER_PROJECTILE);
	texBolt->setRelativePath(strFilePath);

	Vec2 vScale = { texBolt->getWidth(), texBolt->getHeight() };
	SetScale(vScale);

	CreateCollider();
	//getCollider()->setOffsetPos(vScale/2);
	getCollider()->setScale(vScale);
	getCollider()->setOffsetPos({ vScale.x/2,vScale.y/2 });


	vDir = _dir;
	vDir.Normalize();

	fSpeed = _fspeed;
	iSkillNum = 1;
	fDTAccum = 0;
	eType = MISSILE_TYPE::THUNDERBOLT;
}

void CMissile::PikachuUltimateTexture()
{
	iUltimateNum = UltiCnt % 12;
		wstring strTag = L"Ultimate" + to_wstring(iUltimateNum);
		wstring strPath = L"Texture\\monster\\pikachu\\Ultimate\\" + strTag + L".bmp";
		texPikaUlti[iUltimateNum] = CResMgr::GetInst()->LoadTexture(strTag, strPath);
		texPikaUlti[iUltimateNum]->setRelativePath(strPath);
}

void CMissile::PikachuUltimate(Vec2 _center)
{
	PikachuUltimateTexture();
	int j = iUltimateNum;
	Vec2 vScale = { texPikaUlti[j]->getWidth(),texPikaUlti[j]->getHeight() };
	SetScale(vScale);

	
	CreateCollider();
	getCollider()->setScale(vScale);
	Vec2 vOffset = Vec2(texPikaUlti[j]->getWidth() / 2, texPikaUlti[j]->getHeight() / 2);
	getCollider()->setOffsetPos(vOffset);

	//Position
	SetPosition(_center);

	//Vector
	Vec2 vVectorTo = Vec2(rand() % 200 - 100, rand() % 200 - 100);
	if (vVectorTo.x == 0 && vVectorTo.y == 0) vVectorTo = (10, 10);
	if (vVectorTo.x == 0) vVectorTo.x = vVectorTo.y;
	if (vVectorTo.y == 0)vVectorTo.y = vVectorTo.x;

	vDir = vVectorTo;
	vDir.Normalize();

	fSpeed = 300;

	eType = MISSILE_TYPE::PIKACHU_ULTIMATE;
	setGroup(GROUP_TYPE::PLAYER_PROJECTILE);
	fDTAccum = 0;
	UltiCnt++;
}

void CMissile::SpreadSwamp()
{
	texSwamp = CResMgr::GetInst()->LoadTexture(L"Swamp", L"Texture\\monster\\bulbasaur\\Swamp.bmp");
	wstring strFilePath = texSwamp->getRelativePath();
	strFilePath += L"Texture\\monster\\bulbasaur\\Swamp.bmp";
	setGroup(GROUP_TYPE::PLAYER_DEBUFF);
	texSwamp->setRelativePath(strFilePath);

	Vec2 vScale = { texSwamp->getWidth(), texSwamp->getHeight() };
	SetScale(vScale);

	CreateCollider(); 
	getCollider()->setScale(vScale * 0.8);
	getCollider()->setOffsetPos(Vec2(-5, 10));
	//getCollider()->setOffsetPos({ vScale.x / 2,vScale.y / 2 });

	vCenter = CSceneMgr::GetInst()->GetCurrentScene()->GetPlayer()->GetPosition();
	SetPosition(vCenter);

	vDir = (0, 0);
	fSpeed = 0;

	eType = MISSILE_TYPE::SWAMP;
	fDTAccum = 0;
}

bool CMissile::is_Alive()
{
	LARGE_INTEGER crntTime;
	QueryPerformanceCounter(&crntTime);
	return crntTime.QuadPart <= endTime.QuadPart;
}


void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	//player projectile
	if (_pOther->getOwnerObject()->getGroup() == GROUP_TYPE::MONSTER)
	{
		myDeleteObject(this, GROUP_TYPE::PLAYER_PROJECTILE);
	}
	if(eType==MISSILE_TYPE::LAZORLEAFT)
	{
		if (_pOther->getOwnerObject()->getGroup() == GROUP_TYPE::PLAYER_PROJECTILE)
		{
			myDeleteObject(this, GROUP_TYPE::MONSTER_PROJECTILE);
		}
	}
	if(eType==MISSILE_TYPE::THUNDERBOLT||eType==MISSILE_TYPE::PIKACHU_ULTIMATE)
	{
		if (_pOther->getOwnerObject()->getGroup() == GROUP_TYPE::MONSTER_PROJECTILE)
		{
			myDeleteObject(this, GROUP_TYPE::PLAYER_PROJECTILE);
		}
	}
}

void CMissile::OnCollision(CCollider* _pOther)
{

}

void CMissile::OnCollisionExit(CCollider* _pOther)
{
}

CMissile::CMissile()
	:fSpeed(0),
	vDir{}
{
	// >> : create componenets
	//getCollider()->setScale({ 10,10 });
	// << : create componenets
}

CMissile::CMissile(Point _pos, Point _scale)
	:fSpeed(0),
	vDir{Vec2(1,1)} 
{
	vDir.Normalize();

	SetPosition(_pos);
	SetScale(_scale);
}

CMissile::~CMissile()
{
} 

void CMissile::HitOCG()
{
	CScene* crntScene = CSceneMgr::GetInst()->GetCurrentScene();
	PackOCG packOCG = crntScene->GetPlayer()->GetOCGPack();
	Point pCenter = vCenter.ToPoint();
	Point pScale = GetScale();
	pCenter.x += pScale.x / 2; 
	pCenter.y += pScale.y / 2;
	for (int i = 0; i < packOCG.ocgCnt; i++)
	{
		if (IsBetweenY(packOCG.ocgPoint[i], packOCG.ocgPoint[i + 1], pCenter))
		{
			if(IsBetweenTwo(packOCG.ocgPoint[i].x+2, packOCG.ocgPoint[i].x-2,pCenter.x))
				crntScene->GetPlayer()->GoBackOCG0();
		}
		if (IsBetweenX(packOCG.ocgPoint[i], packOCG.ocgPoint[i + 1], pCenter))
		{
			if (IsBetweenTwo(packOCG.ocgPoint[i].y + 2, packOCG.ocgPoint[i].y - 2, pCenter.y))
				crntScene->GetPlayer()->GoBackOCG0();
		}
	}
}