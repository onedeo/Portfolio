#pragma once
#include "pch.h"
class CTexture;
class CSound;

class CResMgr
{
	SINGLE(CResMgr);
private:
	map<wstring, CTexture*> mapTex;
	map<wstring, CSound*> mapSnd;

public:
	CTexture* FindTexture(const wstring& _strKey);
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);

	CSound* FindSound(const wstring& _strKey);
	CSound* LoadSound(const wstring& _strKey, const wstring& _strRelativePath,bool _loop);
};

