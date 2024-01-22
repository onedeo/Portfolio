#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"

CCore::CCore()
	: hWnd(0)
	, ptResolution{}
	, hDC(0)
	, hBit(0)
	, memDC(0)
	, arrBrush{}
	, arrPen{}
{
}

CCore::~CCore()
{
	ReleaseDC(hWnd, hDC);

	DeleteDC(hDC);
	DeleteObject(hBit);

	//delete PEN
	for (int i = 0; i < (int)PEN_TYPE::END; i++)
	{
		DeleteObject(arrPen[i]);
	}
}

int CCore::init(HWND _hWnd, Point _ptResolution)
{
	bCleared = false;
	hWnd = _hWnd;
	ptResolution = _ptResolution;
	
	//해상도에 맞게 윈도우 크기 조정
	RECT rt = { 0,0,ptResolution.x, ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(hWnd, nullptr, 300, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	//OCD크기 조정
	int blank = 100;
	rectOCDTotalSize.left = blank;
	rectOCDTotalSize.top = blank;
	rectOCDTotalSize.right = ptResolution.x - blank;
	rectOCDTotalSize.bottom = ptResolution.y - blank;

	hDC = GetDC(hWnd);

	//double buffering
	hBit = CreateCompatibleBitmap(hDC, ptResolution.x, ptResolution.y);
	memDC = CreateCompatibleDC(hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(memDC, hBit);
	DeleteObject(hOldBit);

	CreateBrushPen();

	//Manager 초기화
	CPathMgr::GetInst()->Init();
	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	CSceneMgr::GetInst()->Init();
	CCollisionMgr::GetInst()->Init();

	iStage = 1;

	return S_OK;
}



void CCore::Progress()
{
	//==============
	//Manager Update
	//=============
	CTimeMgr::GetInst()->Update();
	CKeyMgr::GetInst()->Update();

	//=========
	//SceneUpdate
	//=========


	CSceneMgr::GetInst()->Update();
	CCollisionMgr::GetInst()->Update();

	//=========
	//RENDERING
	//=========
	
	//화면 Clear
	Rectangle(memDC, -1, -1, ptResolution.x + 1, ptResolution.y + 1);

	CSceneMgr::GetInst()->Render(memDC);

	//BitBlt: 한 화면의 픽셀을 모두 복붙하는거
	BitBlt(hDC, 0, 0, ptResolution.x, ptResolution.y, memDC, 0, 0, SRCCOPY);

	// =================
	//EventManager Update
	//=================
	CEventMgr::GetInst()->Update();
}

HWND CCore::get_MainHwnd()
{
	return hWnd;
}

void CCore::CreateBrushPen()
{
	//hollow brush (dont need to delete)
	arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	arrBrush[(UINT)BRUSH_TYPE::YELLOW] = CreateSolidBrush(RGB(255, 255, 0));
	arrBrush[(UINT)BRUSH_TYPE::BLUE] = CreateSolidBrush(RGB(0, 0, 255));
	arrBrush[(UINT)BRUSH_TYPE::GREEN] = CreateSolidBrush(RGB(0, 200, 0));
	arrBrush[(UINT)BRUSH_TYPE::BLACK] = CreateSolidBrush(RGB(255, 255, 255));
	//red pen
	arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	arrPen[(UINT)PEN_TYPE::YELLOW] = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));

}
