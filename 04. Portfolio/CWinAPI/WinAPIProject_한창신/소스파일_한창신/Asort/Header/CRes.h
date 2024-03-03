#pragma once
#include "pch.h"


class CRes
{


private:
	wstring strKey;					// 리소스 키
	wstring strRelativePath;		// 리소스 상대경로

public:
	void setKey(const wstring& _strKey) { strKey = _strKey; }
	void setRelativePath(const wstring& _strPath) { strRelativePath = _strPath; }

	const wstring& getKey() { return strKey; }
	const wstring& getRelativePath() { return strRelativePath; }

public:
	CRes();
	virtual ~CRes();

};

