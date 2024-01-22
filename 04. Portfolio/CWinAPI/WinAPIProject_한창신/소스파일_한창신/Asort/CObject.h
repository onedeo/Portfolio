#pragma once
#include"pch.h"


class CCollider;
class CEventMgr;

class CObject
{
private:
	GROUP_TYPE	eGroup;
	wstring				strTag;

	Vec2					vCenter;
	Vec2					vScale;

	CCollider* pCollider;
	bool bAlive;

public:
	void SetPosition(Point _pCen) { vCenter = _pCen.ToVec2(); }
	void SetPosition(Vec2 _vCen) { vCenter = _vCen; }
	void SetScale(Point _pScale) { vScale = _pScale.ToVec2(); }
	void SetScale(Vec2 _vScale) { vScale = _vScale; }
	
	Vec2 GetPosition() { return vCenter; }
	Vec2 GetScale() { return vScale; }

	void SetTag(const wstring& _strTag) { strTag = _strTag; }
	const wstring& GetTag() { return strTag; }

	void setGroup(GROUP_TYPE _eType) { eGroup = _eType; }
	GROUP_TYPE getGroup() { return eGroup; }

	void setTag(const wstring& _strTag) { strTag = _strTag; }
	const wstring& getTag() { return strTag; }

	bool IsDead() { return !bAlive; }
	

	// ☆ 컴포넌트 추가하면 컴포넌트 렌더도 할것

	void CreateCollider();
	CCollider* getCollider() { return pCollider; }

	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

	// my additional functions
	virtual void ResetToStart() {}
	
private:
	void setDead() { bAlive = false; }




public:
	virtual void Update() = 0;
	virtual void FinalUpdate() final; //여기 이상으로 오버라이딩 안되게 하는 기능 ->final
	virtual void Render(HDC _dc);

	void ComponentRender(HDC _dc);

public:
	CObject();
	CObject(Vec2 _Pos, Vec2 _Scale);
	virtual ~CObject();



	friend class CEventMgr;
};
