#pragma once
#include "pch.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CUI.h"
#include "CPokemon.h"
#include "COcuppied.h"

//���� ����
class CObject;
class CPlayer;
class COcuppied;
class CUI;

class CScene
{
private:
	//������Ʈ �����ͷ� �����ϴ� ����: ��� ������Ʈ�� �θ�Ÿ���� CObject�̱� ����
	//-> �ڽ��� �����ʹ� �θ������Ͱ� ��� ���� �� ����
	vector<CObject*> arrObj[(UINT)GROUP_TYPE::END]; 
	//������Ʈ�� �׷캰(�迭) �� ������Ʈ(����)�� ����
	wstring					strName;

	COcuppied* OCD;
	CPlayer* player;
	CEnemy* enemy;
	CUI* ui;

public:
	void set_Name(const wstring& _strName) { strName = _strName; }
	const wstring& GetName() { return strName; }

	virtual void Enter() = 0; // �� ����
	virtual void Exit() = 0;	// �� Ż��

	virtual void PlayerLoseLife() {};
	virtual void PokemonUseUltimate(int _ultimate) {};
	// �߻�Ŭ������ ����� ��üȭ�� �� ����
	// �ڽ� Ŭ������ �ش� �Լ��� ������ �������� �ȵȴ�.

	COcuppied* GetOCD(){ return OCD; } //OCD virtual
	CPlayer* GetPlayer() { return player; }
	CEnemy* GetEnemy() { return enemy; }
	CUI* GetUI() { return ui; }
	
	void SetOCD(COcuppied* _OCD) { OCD = _OCD; }
	void SetPlayer(CPlayer* _player) { player = _player; }
	void SetEnemy(CEnemy* _enemy) { enemy = _enemy; }
	void SetUI(CUI* _ui) { ui = _ui; }

	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);

	void DeleteGroup(GROUP_TYPE _eGroup);
	void DeleteAll();

public:
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		arrObj[(UINT)_eType].push_back(_pObj);
	}

	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return arrObj[(UINT)_eType]; }


public:
	CScene();
	virtual ~CScene();

};

