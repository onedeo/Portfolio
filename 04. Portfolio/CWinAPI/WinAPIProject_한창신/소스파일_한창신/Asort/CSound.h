#pragma once
#include "CRes.h"
#include "pch.h"

class CSound :
    public CRes
{
private:

public:
    void Load(const wstring& _strFilePath, bool _loop);

private:
    CSound();
    ~CSound();
    friend class CResMgr;
};

