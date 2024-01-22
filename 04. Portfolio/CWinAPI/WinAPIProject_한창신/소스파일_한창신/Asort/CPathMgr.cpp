#include "CPathMgr.h"
#include "CCore.h"

CPathMgr::CPathMgr()
	:szcontentPath{}
{}

CPathMgr::~CPathMgr()
{}


void CPathMgr::Init()
{
	//GetCurrentDirectory(255, szcontentPath);
	
	int iLen = wcslen(szcontentPath);

	for (int i = iLen - 1; 0<=i; i--)
	{
		if (szcontentPath[i] == '\\')
		{
			szcontentPath[i] = 0;
			break;
		}
	}
	wcscat_s(szcontentPath, 255, L"Contents\\");
}
