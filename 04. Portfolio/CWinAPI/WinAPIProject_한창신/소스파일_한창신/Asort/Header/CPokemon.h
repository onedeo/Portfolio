#pragma once
#include "CObject.h"
#include "CTexture.h"

enum class STATE { FOLLOW, COME_BACK, USE_SKILL };
class CPokemon :
    public CObject
{
private:
    Vec2 vCenter;
    Vec2 vCenTemp;
    Vec2 vPlayer;

    Vec2 vDir;
    int maxLoadPosition;

    Vec2 vScale;
    DIRECTION eDirPlayer;
    DIRECTION eDirCrnt;

    STATE eState;
    float fSpeed;
    float fSpeedBack;

    float fDTAccum;
    int iBoltQuant;
    float fBoltLeft;
    int iBoltCool;

    int iUltimate;
    float fUltimateLeft;
    int iUltimateCool;

    CTexture* pTex;

public:
    CPokemon();
    ~CPokemon();

    virtual void Update();
    virtual void Render(HDC _dc);
    void RenderGage(HDC _dc);
    void IncreaseUltimate();
    void Init();

private:
    void FollowPosition();
    void ComeBack();
    void PositionUsingSkill();
    void ThunderBolt();
    void CreateThunderBolt(Vec2 _dir, float _fspeed);
   
    void Ultimate();
};

