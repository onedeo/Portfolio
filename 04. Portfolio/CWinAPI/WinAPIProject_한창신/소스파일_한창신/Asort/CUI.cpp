#include "CUI.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CCore.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "SelectGDI.h"
#include "CSound.h"

void CUI::Render(HDC _dc)
{
	
	BitBlt(_dc, 0, 0, pResolution.x, pResolution.y, texBackground->getDC(), 0, 0, SRCCOPY);
	
	
	for (int i = 0; i<iLife; i++)
	{
		TransparentBlt(_dc, pLife.x + i * 50, pLife.y, vLifeScale.x, vLifeScale.y, texLife->getDC(), 0, 0, vLifeScale.x, vLifeScale.y, RGB(255, 0, 255));
	}


	for (int i = 0; i < iUltimate; i++)
	{
		TransparentBlt(_dc, pUltimate.x - i * 50, pUltimate.y, vUltimateScale.x, vUltimateScale.y, texUltimate->getDC(), 0, 0, vUltimateScale.x, vUltimateScale.y, RGB(255, 0, 255));
	}
	Rectangle(_dc, rectGage.left, rectGage.top, rectGage.right, rectGage.bottom);
	SelectGDI brush(_dc, BRUSH_TYPE::GREEN);
	Rectangle(_dc, rectLeft.left, rectLeft.top, rectLeft.right, rectLeft.bottom);
	TransparentBlt(_dc, pProgressCenter.x, pProgressCenter.y, pProgressScale.x, pProgressScale.y, texProgress->getDC(), 0, 0, pProgressScale.x, pProgressScale.y, RGB(255, 255, 255));

 }

void CUI::Update()
{
	fOCDArea = crntScene->GetOCD()->GetOCDArea();
	float iOCDRatio = (fOCDArea / fTotalArea);
 	rectLeft.right =rectLeft.left+(rectGage.right-rectLeft.left) * iOCDRatio;
}

void CUI::UpdateLife(int _life)
{
	iLife = _life;
}

void CUI::UpdateUltimate(int _ultimate)
{
	iUltimate = _ultimate;
}

CUI::CUI()
{
	Init();
}

CUI::~CUI()
{
}

void CUI::Init()
{
	pResolution = CCore::GetInst()->get_Resolution();
	crntScene = CSceneMgr::GetInst()->GetCurrentScene();
	fTotalArea = crntScene->GetOCD()->GetTotalArea();


	texBackground = CResMgr::GetInst()->LoadTexture(L"Background", L"Texture\\UI\\Background.bmp");
	wstring strFilepath = CPathMgr::GetInst()->getContentPath();
	strFilepath += L"Texture\\UI\\Background.bmp";
	texBackground->Load(strFilepath);
	
	texLife = CResMgr::GetInst()->LoadTexture(L"Life", L"Texture\\UI\\Life.bmp");
	strFilepath = CPathMgr::GetInst()->getContentPath();
	strFilepath += L"Texture\\UI\\Life.bmp";
	texLife->Load(strFilepath);
	vLifeScale = Vec2(texLife->getWidth(), texLife->getHeight());
	pLife = Point(100, 20);

	texUltimate=CResMgr::GetInst()->LoadTexture(L"Ultimate", L"Texture\\UI\\Ultimate.bmp");
	strFilepath = CPathMgr::GetInst()->getContentPath();
	strFilepath += L"Texture\\UI\\Ultimate.bmp";
	texUltimate->Load(strFilepath);
	vUltimateScale = Vec2(texUltimate->getWidth(), texUltimate->getHeight());
	pUltimate = Point(pResolution.x - 150, 40);

	texProgress = CResMgr::GetInst()->LoadTexture(L"Progress", L"Texture\\UI\\progress.bmp");
	strFilepath = CPathMgr::GetInst()->getContentPath();
	strFilepath += L"Texture\\UI\\progress.bmp";
	texProgress->Load(strFilepath);
	pProgressScale = Vec2(texProgress->getWidth(), texProgress->getHeight());
	pProgressCenter = Point(780, 670);

	rectGage.top = 710;
	rectGage.left = 860;
	rectGage.right = rectGage.left + 300;
	rectGage.bottom = rectGage.top+20;
	rectLeft = rectGage;

	wstring strTag = L"MusicStart";
	wstring strPath = L"Sound\\" + strTag + L".wav";
	sndBG = CResMgr::GetInst()->LoadSound(strTag, strPath,true);
	sndBG->Load(strTag, true);




}
