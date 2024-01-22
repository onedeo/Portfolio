#pragma once
#include "pch.h"
#include <Windows.h>
#include "define.h"

class CTimeMgr
{
	SINGLE(CTimeMgr);

private:
	//fps 를 구해서 1프레임당 시간 :  Delta Time
	LARGE_INTEGER	llCurCount;
	LARGE_INTEGER	llFrequency;
	LARGE_INTEGER	llPrevCount;
	double					dDT; //프레임 간의 시간값


public:
	void Init();
	void Update();

public:
	double GetdDT() { return dDT; }
	float GetfDT() { return (float)dDT; }
};

