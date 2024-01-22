#pragma once
#include "pch.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CUI.h"
#include "CPokemon.h"
#include "COcuppied.h"

//전방 선언
class CObject;
class CPlayer;
class COcuppied;
class CUI;

class CScene
{
private:
	//오브젝트 포인터로 관리하는 이유: 모든 오브젝트의 부모타입이 CObject이기 때문
	//-> 자식의 포인터는 부모포인터가 모두 받을 수 있음
	vector<CObject*> arrObj[(UINT)GROUP_TYPE::END]; 
	//오브젝트를 그룹별(배열) 각 오브젝트(벡터)로 관리
	wstring					strName;

	COcuppied* OCD;
	CPlayer* player;
	CEnemy* enemy;
	CUI* ui;

public:
	void set_Name(const wstring& _strName) { strName = _strName; }
	const wstring& GetName() { return strName; }

	virtual void Enter() = 0; // 씬 진입
	virtual void Exit() = 0;	// 씬 탈출

	virtual void PlayerLoseLife() {};
	virtual void PokemonUseUltimate(int _ultimate) {};
	// 추상클래스를 만들면 객체화할 수 없다
	// 자식 클래스가 해당 함수가 없으면 컴파일이 안된다.

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

