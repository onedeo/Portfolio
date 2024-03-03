#pragma once
#include "CObject.h"

class CSound;
class CTexture;

class CClosing :
    public CObject
{
private:
    CTexture* texClosingBG;
    Vec2 vCenter;
    Vec2 vDir;
    Point pScale;
    float fSpeed;
    float fDTAccum;

    CTexture* texMewtwo;
    CTexture* texMewtwo1;
    bool bMewtwo;

    CTexture* texThankyou;

    Point pResolution;
    bool bCleared;
    bool bSpacebar;

    CSound* sndClosing;
    CSound* sndMewtwo;

public:
    CClosing();
    ~CClosing();

    virtual void Update();
    virtual void Render(HDC _dc);

    void Init();
    void ShowMewtwo();


};

