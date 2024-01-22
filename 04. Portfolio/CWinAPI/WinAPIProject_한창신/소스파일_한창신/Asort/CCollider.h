#pragma once
#include "pch.h"

class CObject;

class CCollider
{
private:
	static UINT g_iNextID;

	CObject* pOwner;

	Vec2			pScale; //collider size

	Vec2			vOffsetPos;
	Vec2			vFinalPos; // object위치와 offset을 계산해서 최종 collider 위치 산출

	int			iCol; //Collision 여부

	UINT iID; //충돌체 고유 아이디

	

public:
	void setScale(Vec2 _scale) { pScale = _scale; }
	void setOffsetPos(Vec2 _offset) { vOffsetPos = _offset; }
	UINT getID() { return iID; }

	Vec2 getOffsetPos() { return vOffsetPos; }
	Vec2 getScale() { return pScale; }
	Vec2 getFinalPos() { return vFinalPos; }

	CObject* getOwnerObject() { return pOwner; }

public:
	void FinalUpdate();
	void Render(HDC _dc);

public: //충돌 시점 함수
	void OnCollision(CCollider* _pOther); //충돌 중인 경우 호출되는 함수
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

	CCollider& operator = (CCollider& _origin) = delete;
public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

	friend class CObject;
};

