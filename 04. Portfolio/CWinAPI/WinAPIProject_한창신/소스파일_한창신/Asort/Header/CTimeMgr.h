#pragma once
#include "pch.h"
#include <Windows.h>
#include "define.h"

class CTimeMgr
{
	SINGLE(CTimeMgr);

private:
	//fps �� ���ؼ� 1�����Ӵ� �ð� :  Delta Time
	LARGE_INTEGER	llCurCount;
	LARGE_INTEGER	llFrequency;
	LARGE_INTEGER	llPrevCount;
	double					dDT; //������ ���� �ð���


public:
	void Init();
	void Update();

public:
	double GetdDT() { return dDT; }
	float GetfDT() { return (float)dDT; }
};

