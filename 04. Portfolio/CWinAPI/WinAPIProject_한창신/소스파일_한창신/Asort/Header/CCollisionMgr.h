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
	map<ULONGLONG, bool>   mapColInfo;													//�浹ü ���� ���� ������ �浹 ����
	UINT									arrCheck[(UINT)GROUP_TYPE::END];			//�׷찣�� �浹 üũ ��Ʈ����

public:
	void Init();
	void Update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void ResetGroup();

private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	bool IsCollision(CCollider* _pLeft, CCollider* _pRight);

};

