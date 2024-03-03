#include "../Header/CTexture.h"
#include "../Header/CCore.h"


HBITMAP CTexture::Load(const wstring& _strFilePath)
{
	//���Ϸ� ���� �ε��� �����͸� ��Ʈ������ ����
	hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(hBit);
	
	//��Ʈ�ʰ� ������ DC
	DC = CreateCompatibleDC(CCore::GetInst()->getMainDC());
	HBITMAP hPrevBit = (HBITMAP)SelectObject(DC, hBit);
	DeleteObject(hPrevBit);

	//���� ���� ����
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
