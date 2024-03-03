#include "../Header/CObject.h"
#include "../Header/CKeyMgr.h"
#include "../Header/define.h"
#include "../Header/CCollider.h"

void CObject::CreateCollider()
{
	pCollider = new CCollider;
	pCollider->pOwner = this; //�ֹ濬��
}

void CObject::Update()
{


}

void CObject::FinalUpdate()
{
	if (pCollider)
		pCollider->FinalUpdate();
}

void CObject::Render(HDC _dc)
{
	Point pCenter = vCenter.ToPoint();
	Point pScale = vScale.ToPoint();
	Rectangle(_dc, (pCenter.x - pScale.x/2), (int)(pCenter.y - pScale.y / 2),
		(int)(pCenter.x + pScale.x / 2), (int)(pCenter.y + pScale.y / 2));
	
	ComponentRender(_dc);
}

void CObject::ComponentRender(HDC _dc)
{
	if (pCollider != nullptr) pCollider->Render(_dc);
}

CObject::CObject()
	:vCenter{}
	, vScale{}
	, pCollider(nullptr)
	, bAlive(true)
{}

CObject::CObject(Vec2 _Pos, Vec2 _Scale)
{
	vCenter = _Pos;
	vScale = _Scale;
}

CObject::~CObject()
{
	if (pCollider != nullptr)
		delete pCollider;
}
