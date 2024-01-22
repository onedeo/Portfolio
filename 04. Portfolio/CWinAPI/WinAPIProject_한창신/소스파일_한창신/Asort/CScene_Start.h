#pragma once
#include "CScene.h"

class CSound;

class CScene_Start:
	public CScene
{
private:
	int iLife;
	int iUltimate;

	CSound* sndLose;

public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();


public:
	virtual void PlayerLoseLife();
	virtual void PokemonUseUltimate(int _ultimate);

public:
	CScene_Start();
	~CScene_Start();
};