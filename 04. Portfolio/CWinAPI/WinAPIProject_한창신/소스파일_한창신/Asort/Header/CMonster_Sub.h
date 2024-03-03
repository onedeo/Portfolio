#pragma once
#include "CObject.h"
#include "CTexture.h"

enum class STATE_MS{LEAF, EMPTY};

class CMonster_Sub :
    public CObject
{
private:
    Vec2 vCenter;
    Vec2 vScale;
    float fDTAccum;
    STATE_MS eState;

    CTexture* texTreeFull;
    CTexture* texTreeEmpty;

public:
    CMonster_Sub();
    ~CMonster_Sub();

    virtual void Render(HDC _dc);
    virtual void Update();

    void Init();

    void CreateRazorLeaf();
    void CreateLeaf(Vec2 _dir, float _fspeed);


};

