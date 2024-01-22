#pragma once
#include "pch.h"

class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr);
private:
	SCENE_TYPE crntScene;

	CScene* arrScene[(UINT)SCENE_TYPE::END]; //¸ðµç ¾À
	CScene* pCurScene; //ÇöÀç ¾À


public:
	void Init();
	void Update();
	void Render(HDC _dc);

public:
	CScene* GetCurrentScene() { return pCurScene; }
private:
	void ChangeScene(SCENE_TYPE _scene);
	friend class CEventMgr;
};

