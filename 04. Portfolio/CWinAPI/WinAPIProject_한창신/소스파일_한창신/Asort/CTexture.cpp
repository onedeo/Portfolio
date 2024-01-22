#include "CTexture.h"
#include "CCore.h"


HBITMAP CTexture::Load(const wstring& _strFilePath)
{
	//파일로 부터 로딩한 데이터를 비트맵으로 생성
	hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(hBit);
	
	//비트맵과 연결할 DC
	DC = CreateCompatibleDC(CCore::GetInst()->getMainDC());
	HBITMAP hPrevBit = (HBITMAP)SelectObject(DC, hBit);
	DeleteObject(hPrevBit);

	//가로 세로 길이
	GetObject(hBit, sizeof(BITMAP), &tInfo);

	return hBit;
}

CTexture::CTexture() 
	:DC(0),
	hBit(0),
	tInfo {}
{
}

CTexture::~CTexture()
{
	delete(DC);
	DeleteObject(hBit);
}
