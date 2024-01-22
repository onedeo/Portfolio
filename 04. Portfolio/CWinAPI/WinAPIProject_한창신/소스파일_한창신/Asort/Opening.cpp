#include "Opening.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CTimeMgr.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CSound.h"

Opening::Opening()
{
	Init();
}

Opening::~Opening() 
{
}

void Opening::Update()
{
	fAccum += fDT;

	if (fAccum > 1)
	{
		
		if (bSwitch)
		{
			pPokemonCenter.x -= fDT * fSpeed * vDir.x * 3;
			NextPokemon();
		}
		else
		{
			pPokemonCenter.x -= fDT * fSpeed * vDir.x;
			OutPokemon();
		}
	}

	if (KEY_AWAY(KEY::SPACE))
	{
		ChangeScene(SCENE_TYPE::START);
	}
}

void Opening::Render(HDC _dc)
{
	RenderBG(_dc);
	RenderLogo(_dc);
	RenderPokemon(_dc);
	RenderAsh(_dc);
}

void Opening::Init()
{
	fSpeed = 500;
	vDir = Vec2(1, 0);
	fAccum = 0;

	wstring strTag;
	wstring strPath;

	// >> : Pokemon Texture
	pPokemonCenter = Point(350, 450);

	for (int i = 0; i < PokemonQuant; i++)
	{
		strTag = L"pokemon" + to_wstring(i);
		strPath = L"Texture\\opening\\pokemon\\" + strTag + L".bmp";
		texPokemon[i] = CResMgr::GetInst()->LoadTexture(strTag, strPath);
		texPokemon[i]->setRelativePath(strPath);
		pPokemonScale[i] = Point(texPokemon[i]->getWidth(), texPokemon[i]->getHeight());
	}
	// << : Pokemon Texture

	// >> : Ash Texture
	pAshCenter = Point(600, 280);
	strTag = L"Ash";
	strPath = L"Texture\\opening\\" + strTag + L".bmp";
	texAsh= CResMgr::GetInst()->LoadTexture(strTag, strPath);
	texAsh->setRelativePath(strPath);
	pAshScale = Point(texAsh->getWidth(), texAsh->getHeight());
	// << : Ash Texture

	// >> : Logo Texture
	pLogoCenter = Point(200, 0);
	strTag = L"Logo";
	strPath = L"Texture\\opening\\" + strTag + L".bmp";
	texLogo= CResMgr::GetInst()->LoadTexture(strTag, strPath);
	texLogo->setRelativePath(strPath);
	pLogoScale = Point(texLogo->getWidth(), texLogo->getHeight());
	// << : Logo Texture

	// >> : BG Texture
	texBackground = CResMgr::GetInst()->LoadTexture(L"OpeningBackground-1", L"Texture\\opening\\Background.bmp");
	wstring strFilepath = CPathMgr::GetInst()->getContentPath();
	strFilepath += L"Texture\\opening\\Background.bmp";
	texBackground->Load(strFilepath);
	pResolution = CCore::GetInst()->get_Resolution();
	// << : BG Texture;
	 
	strTag = L"MusicOpening";
	strPath = L"Sound\\" + strTag + L".wav";
	sndBG = CResMgr::GetInst()->LoadSound(strTag, strPath,false);
	sndBG->Load(strTag, false);

}

void Opening::RenderPokemon(HDC _dc)
{
	int i = iPokemon;
	
	pTempCenter = pPokemonCenter;
	pTempScale = pPokemonScale[i];
	TransparentBlt(_dc, pTempCenter.x, pTempCenter.y, pTempScale.x, pTempScale.y,
				   texPokemon[i]->getDC(), 0, 0, pTempScale.x, pTempScale.y, RGB(255, 0, 255));
}

void Opening::RenderLogo(HDC _dc)
{
	pTempCenter = pLogoCenter;
	pTempScale = pLogoScale;
	TransparentBlt(_dc, pTempCenter.x, pTempCenter.y, pTempScale.x, pTempScale.y,
				  texLogo->getDC(), 0, 0, pTempScale.x, pTempScale.y, RGB(255, 0, 255));
}

void Opening::RenderAsh(HDC _dc)
{
	pTempCenter = pAshCenter;
	pTempScale = pAshScale;
	TransparentBlt(_dc, pTempCenter.x, pTempCenter.y, pTempScale.x, pTempScale.y,
				   texAsh->getDC(), 0, 0, pTempScale.x, pTempScale.y, RGB(255, 0, 255));
}

void Opening::RenderBG(HDC _dc)
{
BitBlt(_dc, 0, 0, pResolution.x, pResolution.y, texBackground->getDC(), 0, 0, SRCCOPY);
}

void Opening::OutPokemon()
{
		if ((pPokemonCenter.x) < 0)
		{
			iPokemon = (iPokemon + 1) % PokemonQuant;
			pPokemonCenter.x = 1200;
			bSwitch = !bSwitch;
		}
}

void Opening::NextPokemon()
{
		
	if (pPokemonCenter.x < 350)
	{
		fAccum = 0;
		bSwitch = !bSwitch;
	}
}
