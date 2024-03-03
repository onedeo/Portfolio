#pragma once
#include "pch.h"

struct tEvent
{
	EVENT_TYPE				eEvent;
	DWORD_PTR			lParam;
	DWORD_PTR			wParam;
};

class CEventMgr
{
	SINGLE(CEventMgr);
private:
	vector<tEvent> vecEvent;
	vector<CObject*> vecDead;

public:
	void Update();
	void AddEvent(const tEvent& _event) { vecEvent.push_back(_event); }


private:
	void Execute(const tEvent& _eve);
};

