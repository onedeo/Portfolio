#include "CSound.h"
#include "mmsystem.h"
#pragma comment(lib, "winmm.lib")

void CSound::Load(const wstring& _strFilePath, bool _loop)
{
	LPCWSTR str = _strFilePath.c_str();
	if (_loop)
		PlaySound(str, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT | SND_LOOP);
	else
		PlaySound(str, NULL, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
}

CSound::CSound()
{
}

CSound::~CSound()
{
}
