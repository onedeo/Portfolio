#include "../Header/CCollider.h"
#include "../Header/CObject.h"
#include "../Header/CCore.h"
#include"../Header/SelectGDI.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: pOwner(nullptr)
	, iID(g_iNextID++)
	, iCol(false)
{
}

CCollider::~CCollider()
{
}

CCollider::CCollider(const CCollider& _origin)
	:pOwner(nullptr)
	,vOffsetPos(_origin.vOffsetPos)
	,pScale(_origin.pScale)
	,iID(g_iNextID++)
{
}

void CCollider::OnCollision(CCollider* _pOther)
{
	pOwner->OnCollision(_pOther);
}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	pOwner->OnCollisionEnter(_pOther);
	iCol++; //�浹�ߺ����� �浹���� ī��Ʈ
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	pOwner->OnCollisionExit(_pOther);
	iCol--;
}

void CCollider::FinalUpdate()
{
	assert(0 <= iCol);
	//follow Object
	Point vObjectPos = pOwner->GetPosition();
	vFinalPos = vObjectPos.ToVec2() +vOffsetPos;
}

void CCollider::Render(HDC _dc)
{
	//PEN_TYPE ePen;
	//if (iCol)
	//	ePen = PEN_TYPE::RED;
	//else
	//	ePen = PEN_TYPE::GREEN;

	//SelectGDI pen(_dc, ePen);
	//SelectGDI brush(_dc, BRUSH_TYPE::HOLLOW);

	//Rectangle(_dc,
	//	vFinalPos.x - pScale.x / 2,
	//	vFinalPos.y - pScale.y / 2,
	//	vFinalPos.x + pScale.x / 2,
	//	vFinalPos.y + pScale.y / 2);

}

