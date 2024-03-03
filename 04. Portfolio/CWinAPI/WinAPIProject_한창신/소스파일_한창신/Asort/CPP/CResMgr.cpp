#include "../Header/CResMgr.h"
#include "../Header/CPathMgr.h"
#include "../Header/CTexture.h"
#include "../Header/CSound.h"

CResMgr::CResMgr()
{

}
CResMgr::~CResMgr()
{
	map<wstring, CTexture*>::iterator iter = mapTex.begin();
	for (; iter != mapTex.end(); iter++)
	{
		delete iter->second;
	}
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	map<wstring, CTexture*>::iterator iter = mapTex.find(_strKey);
	if(iter==mapTex.end()) return nullptr;

	return iter->second;
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	CTexture* pTex = FindTexture(_strKey);
	if (pTex != nullptr) return pTex;

	wstring strFilePath = CPathMgr::GetInst()->getContentPath();
	strFilePath += _strRelativePath;

	pTex = new CTexture;
	pTex->Load(strFilePath);

	pTex->setKey(_strKey);
	pTex->setRelativePath(_strRelativePath);

	mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

CSound* CResMgr::FindSound(const wstring& _strKey)
{
	map<wstring, CSound*>::iterator iter = mapSnd.find(_strKey);
	if (iter == mapSnd.end()) return nullptr;

	return iter->second;
}

CSound* CResMgr::LoadSound(const wstring& _strKey, const wstring& _strRelativePath,bool _loop)
{
	CSound* pSnd = FindSound(_strKey);
	if (pSnd != nullptr)return pSnd;

	wstring strFilePath = CPathMgr::GetInst()->getContentPath();
	strFilePath += _strRelativePath;

	pSnd = new CSound;
	pSnd->Load(strFilePath, _loop);

	pSnd->setKey(_strKey);
	pSnd->setRelativePath(_strRelativePath);

	mapSnd.insert(make_pair(_strKey, pSnd));

	return pSnd;
}
