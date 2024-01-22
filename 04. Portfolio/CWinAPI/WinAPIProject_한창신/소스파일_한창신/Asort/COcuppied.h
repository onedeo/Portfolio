#pragma once
#include "CObject.h"
#include "CTexture.h"

class CSound;
class COcuppied :
    public CObject
{
private:

    Vec2 vEnemyCen;
    PackOCG ocgPack;

    OCDPoint* ocdDeleteStart;
    OCDPoint* ocdDeleteEnd;   
    OCDPoint* ocdAddStart;
    bool Sannabi;
    bool bStartOCGonOCD;
    bool bEndOCGonOCD;
 
    OCDPoint* ocdVec2;

    float fOccupiedAmount;
    bool bShowDebug;

    float fOCDArea;
    float fTotalArea;
    float fTotalPercent;

    bool bFinishGame;
    float fDTFinishGame;

    Vec2 vBallCenter;
    Point pBallScale;
    Vec2 vBallDir;
    float fBallSpeed;

    // >> : Images
    CTexture* texBall;
    CTexture* texBG;
    CTexture* texOCD;
    HBITMAP hBit;
    // << : Images
    CSound* sndWin;

    float FinishRatio;
    float fDTCatch;

public:
    COcuppied();
    ~COcuppied();

public:
    virtual void ResetToStart();
    
    void FinishGame();

    void FinishOCG(PackOCG _ocgPack);
    void OCGSameDirection();

    virtual OCDPoint* GetOCDCrnt() { return ocdVec2; }

    virtual void Update();
    virtual void Render(HDC _dc);
    void UpdateOCDArea();

    float GetTotalArea() { return fTotalArea; }
    float GetOCDArea() { return fOCDArea; }

private:
    bool IsEnemyInOCG();
    
    void ConfigDeletePoint();
    void DeleteOCDPoint();

    void AddOCGPoint();

    void IsOnOCDPoint();
    void StraightOCD();



};

