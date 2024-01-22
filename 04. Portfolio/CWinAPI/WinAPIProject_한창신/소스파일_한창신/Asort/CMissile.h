#pragma once
#include "CObject.h"

class CTexture;
enum class  MISSILE_TYPE
{
    LAZORLEAFT,
    SWAMP,
    THUNDERBOLT,
    PIKACHU_ULTIMATE,
    END
};
class CMissile :
    public CObject
{
private:
    Vec2 vCenter;
    Vec2 vDir;
    MISSILE_TYPE eType;

    float fSpeed;
    
    int iSkillNum;
    float fDTAccum;   

    int iUltimateNum;


    LARGE_INTEGER endTime;

    // >> : Set Images
    CTexture* texLeaf1;
    CTexture* texSwamp;
    HBITMAP hBit;

    CTexture* texBolt;

    CTexture* texPikaUlti[12];
    // << : Set Images

public:
    virtual void Update();
    void UpdateRazorLeaft();
    void UpdateThunderBolt();
    void UpdatePikaUlti();
    void UpdateSwamp();

    virtual void Render(HDC _dc);
    void RenderRazorLeaft(HDC _dc);
    void RenderThunderBolt(HDC _dc);
    void RenderPikaUlti(HDC _dc);
    void RenderSwamp(HDC _dc);


public:
    void set_Direction(float _theta) { vDir = Vec2(cosf(_theta), sinf(_theta)); vDir.Normalize(); }
    void set_Direction(Vec2 _dir) { vDir = _dir; vDir.Normalize(); }
    void SetSpeed(float _sp) { fSpeed = _sp; }

    // >> : RazorLeaf
    void InitLeaf1(Vec2 _dir, float _fspeed);
    void HitOCG();
    bool is_Alive();
    // << : RazorLeaf

    // >> : Swamp
    void SpreadSwamp();

    // << : Swamp

    // >> : ThunderBolt
    void InitThunderBolt(Vec2 _dir, float _fspeed);

    void PikachuUltimateTexture();
    void PikachuUltimate(Vec2 _center);
    // << : ThunderBolt

    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);


public:
    CMissile();
    CMissile(Point _pos, Point _scale);
    ~CMissile();
};

