#pragma once
#include "pch.h"
class CCollider;

union COLLIDER_ID
{
	struct {
		UINT Left_id;
		UINT Right_id;
	};
	ULONGLONG ID;
};


class CCollisionMgr
{
	SINGLE(CCollisionMgr);
private:
	map<ULONGLONG, bool>   mapColInfo;													//충돌체 간의 이전 프레임 충돌 정보
	UINT									arrCheck[(UINT)GROUP_TYPE::END];			//그룹간의 충돌 체크 메트릭스

public:
	void Init();
	void Update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void ResetGroup();

private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* _pLeft, CCollider* _pRight);

};

