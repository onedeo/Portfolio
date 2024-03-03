#include "../Header/CClosing.h"
#include "../Header/CResMgr.h"
#include "../Header/CPathMgr.h"
#include "../Header/CTexture.h"
#include "../Header/CCore.h"
#include "../Header/CTimeMgr.h"
#include "../Header/CKeyMgr.h"
#include "../Header/func.h"
#include "../Header/CSound.h"
#include "../Header/SelectGDI.h"

CClosing::CClosing()
{
	Init();
}

CClosing::~CClosing()
{
}

void CClosing::Update()
{
	if (KEY_TAP(KEY::W)&&KEY_HOLD(KEY::E))
	{
		fSpeed *=4;
	}
	if (KEY_AWAY(KEY::SPACE)&&bSpacebar)
	{
		ChangeScene(SCENE_TYPE::OPENING);
	}
	if (vCenter.x < 5500)
	{
		vCenter.x += fDT * fSpeed * vDir.x;
		vCenter.y += fDT * fSpeed * vDir.y;
	}
	else
	{
		fDTAccum += fDT;
	}
}

void CClosing::Render(HDC _dc)
{
	if (vCenter.x < 5500)
	{
		BitBlt(_dc, 0, 0, pResolution.x, pResolution.y, texClosingBG->getDC(), vCenter.x, vCenter.y, SRCCOPY);
	}
	else if(fDTAccum<=8&&bCleared)
	{
		if (fDTAccum < 0.5)
		{
			wstring strTag = L"MusicMewtwo";
			wstring strPath = L"Sound\\" + strTag + L".wav";
			sndMewtwo = CResMgr::GetInst()->LoadSound(strTag, strPath, false);
			sndMewtwo->Load(strTag, false);
		}
		else if (fDTAccum < 4.7)
		{
			BitBlt(_dc, 0, 0, pResolution.x, pResolution.y, texMewtwo1->getDC(), 0, 0, SRCCOPY);
		}
		else
		{
			BitBlt(_dc, 0, 0, pResolution.x, pResolution.y, texMewtwo->getDC(), 0, 0, SRCCOPY);
		}
	}
	else
	{
		BitBlt(_dc, 0, 0, pResolution.x, pResolution.y, texThankyou->getDC(), 0, 0, SRCCOPY);
		bSpacebar = true;
	}
}

void CClosing::Init()
{
	pResolution = CCore::GetInst()->get_Resolution();

	wstring strTag = L"ClosingBG";
	wstring strPath = L"Texture\\closing\\" + strTag + L".bmp";
	texClosingBG = CResMgr::GetInst()->LoadTexture(strTag, strPath);
	texClosingBG->setRelativePath(strPath);
	pScale = Point(texClosingBG->getWidth(), texClosingBG->getHeight());
	vCenter = Vec2(0, 0);
	vDir = Vec2(10, 0);
	vDir.Normalize();
	fSpeed = 100;

	strTag = L"Mewtwo";
	strPath = L"Texture\\closing\\" + strTag + L".bmp";
	texMewtwo = CResMgr::GetInst()->LoadTexture(strTag, strPath);
	texMewtwo->setRelativePath(strPath);

	strTag = L"Mewtwo1";
	strPath = L"Texture\\closing\\" + strTag + L".bmp";
	texMewtwo1 = CResMgr::GetInst()->LoadTexture(strTag, strPath);
	texMewtwo1->setRelativePath(strPath);

	strTag = L"ThankYou";
	strPath = L"Texture\\closing\\" + strTag + L".bmp";
	texThankyou = CResMgr::GetInst()->LoadTexture(strTag, strPath);
	texThankyou->setRelativePath(strPath);

	strTag = L"MusicClosing";
	strPath = L"Sound\\" + strTag + L".wav";
	sndClosing = CResMgr::GetInst()->LoadSound(strTag, strPath, false);
	sndClosing->Load(strTag,false);

	bCleared = CCore::GetInst()->GetCleared();
	bSpacebar = false;
}

void CClosing::ShowMewtwo()
{
	HWND hWnd = CCore::GetInst()->get_MainHwnd();
	int alpha = 200;
	for (int i = 0; i < alpha; i++)
	{
		SetLayeredWindowAttributes(hWnd, 0, i, LWA_ALPHA);
		Sleep(10);
	}
	for (int i = alpha; 0 < i; i--)
	{
		SetLayeredWindowAttributes(hWnd, 0, i, LWA_ALPHA);
		Sleep(10);
	}
}

