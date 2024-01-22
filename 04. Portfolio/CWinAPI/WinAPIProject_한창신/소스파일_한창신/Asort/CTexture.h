#pragma once
#include "CRes.h"
#include "pch.h"

class CTexture :
    public CRes
{
private:
    HDC             DC;
    HBITMAP     hBit;
    BITMAP          tInfo;

public:
    HBITMAP Load(const wstring& _strFilePath);
    int getWidth() { return tInfo.bmWidth; }
    int getHeight() { return tInfo.bmHeight; }
    HDC getDC() { return DC; }

private:
    CTexture();
    ~CTexture(); 
      friend class CResMgr;
};

