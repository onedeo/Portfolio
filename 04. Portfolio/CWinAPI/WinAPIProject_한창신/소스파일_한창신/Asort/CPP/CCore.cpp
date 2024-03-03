#include "../Header/CCore.h"
#include "../Header/CObject.h"
#include "../Header/CTimeMgr.h"
#include "../Header/CKeyMgr.h"
#include "../Header/CSceneMgr.h"
#include "../Header/CPathMgr.h"
#include "../Header/CCollisionMgr.h"
#include "../Header/CEventMgr.h"

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
	
	//�ػ󵵿� �°� ������ ũ�� ����
	RECT rt = { 0,0,ptResolution.x, ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(hWnd, nullptr, 300, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	//OCDũ�� ����
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

	//Manager �ʱ�ȭ
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
	
	//ȭ�� Clear
	Rectangle(memDC, -1, -1, ptResolution.x + 1, ptResolution.y + 1);

	CSceneMgr::GetInst()->Render(memDC);

	//BitBlt: �� ȭ���� �ȼ��� ��� �����ϴ°�
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
