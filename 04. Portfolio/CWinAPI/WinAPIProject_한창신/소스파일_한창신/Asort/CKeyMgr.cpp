#include"pch.h"

#include "CKeyMgr.h"

#include "CCore.h"

int g_arrVK[(int)KEY::END]
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	VK_SPACE,
	VK_LSHIFT,
	'Q',
	'W',
	'E',
	'R',
	VK_ESCAPE,
	VK_RETURN,
	VK_TAB,
	/*
		LEFT, RIGHT, UP, DOWN,
	SPACE,
	LSHIFT,
	Q,W,E,R,
	ESC,
	ENTER,

	END*/
};

CKeyMgr::CKeyMgr()
{

}
CKeyMgr::~CKeyMgr()
{


}


void CKeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::END; i++)
	{
		vecKey.push_back(tKeyInfo{ KEY_STATE::NONE,false });
	}
}

void CKeyMgr::Update()
{
	//윈도우 포커싱 잡아내기
	HWND hWnd = GetFocus();

	if (hWnd != nullptr) //윈도우 포커싱 ing
	{
		for (int i = 0; i < (int)KEY::END; i++)
		{
			//키가 눌렸다
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				//이전에도 눌려있다.
				if (vecKey[i].bPrevPushed)
					vecKey[i].eState = KEY_STATE::HOLD;
				else
				{
					vecKey[i].eState = KEY_STATE::TAP;
					vecKey[i].bPrevPushed = true;
				}
			}
			else
			{
				if (vecKey[i].bPrevPushed) vecKey[i].eState = KEY_STATE::AWAY;
				else
				{
					vecKey[i].eState = KEY_STATE::NONE;
				}
				vecKey[i].bPrevPushed = false;
			}
		}
	}
	else //윈도우 포커싱 해제 상태
	{
		for (int i = 0; i < (int)KEY::END; ++i)
		{
			vecKey[i].bPrevPushed = false;
			if (vecKey[i].eState == KEY_STATE::TAP || vecKey[i].eState == KEY_STATE::HOLD)
			{
				vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == vecKey[i].eState)
			{
				vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}