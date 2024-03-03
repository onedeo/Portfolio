#pragma once
#include "CObject.h"

class CScene;
class CTexture;
class CSound;

class CUI :
    public CObject
{
private:
    Point pResolution;

    int iLife;
    int iUltimate;
    Point pLife;
    Point pUltimate;
    Point pStat;

    RECT rectGage;
    RECT rectLeft;

    Vec2 vLifeScale;
    Vec2 vUltimateScale;
    Point pProgressScale;

    Point pProgressCenter;

    CTexture* texBackground;
    CTexture* texLife;
    CTexture* texUltimate;
    CTexture* texProgress;

    CSound* sndBG;

    CScene* crntScene;
    float fOCDArea;
    float fTotalArea;

public:
    CUI();
    ~CUI();
    virtual void Render(HDC _dc);
    virtual void Update();

public:
    void UpdateLife(int _life);
    void UpdateUltimate(int _ultimate);

private:
    void Init();
    
};

