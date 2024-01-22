#pragma once
#include "CObject.h"

class CTexture;
class CScene;

enum class ENEMY_STATE { IDLE, SKILL1,PARALYZED,OUTBOUNDARY };

class CEnemy :
    public CObject
{
private:
    Vec2               vCenter;
    Vec2                vScale;
    Vec2                vDir;
    float               fSpeed;
    float               fOriginalSpeed;
    ENEMY_STATE eState;
    
    OCDPoint* ocdCrnt;

    CScene* crntScene;

    float            fDTLeaf1;
    int             fLeaf1Cycle;
    float           fDTIdle;
    int             fIdleDuration;
    float           fDTToCenter;

    float fDTSwamp;
    int fSwampCycle;
    float fDTRecoverSlow;

    int iSlowCount;

    float               fMaxDist;
    // >> : RazorLeaf
    float fDTRazorLeaf;
    // << : RazorLeaf


    CTexture* pTex;

public:
    float GetSpeed() { return fSpeed; }
    void SetSpeed(float _spd) { fSpeed = _spd; }
    void SetCenterPos(Vec2 _cp) { vCenter = _cp; }
    void SetMaxDist(float _md) { fMaxDist = _md; }

    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);

    void HitOCG();

private:
    void Init();
    void CreateLeaf1(Vec2 _dir, float _fspeed);

    // >> : Enemy Move
    void EnemyIdle();
    void OCDBounce();
    bool IsEnemyInOCD();
    void ReturnToBoundary();
    // << : Enemy Move



    // >> : Attacks
    void CreateRazorLeaf();

    void CreateSwamp();

    // << : Attacks

public:
    virtual void Update();
    virtual void Render(HDC _dc);

public:
    CEnemy();
    ~CEnemy();
};

