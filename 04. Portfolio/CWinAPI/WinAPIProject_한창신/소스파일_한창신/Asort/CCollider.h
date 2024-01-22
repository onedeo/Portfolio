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
	Vec2			vFinalPos; // object��ġ�� offset�� ����ؼ� ���� collider ��ġ ����

	int			iCol; //Collision ����

	UINT iID; //�浹ü ���� ���̵�

	

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

public: //�浹 ���� �Լ�
	void OnCollision(CCollider* _pOther); //�浹 ���� ��� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

	CCollider& operator = (CCollider& _origin) = delete;
public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

	friend class CObject;
};

