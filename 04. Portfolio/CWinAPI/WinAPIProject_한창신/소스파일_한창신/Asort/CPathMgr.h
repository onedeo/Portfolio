#pragma once
#include "pch.h"

class CPathMgr
{
	SINGLE(CPathMgr);

private:
	wchar_t			szcontentPath[255];

public:
	void Init();
	const wchar_t* getContentPath() { return szcontentPath; }
};

