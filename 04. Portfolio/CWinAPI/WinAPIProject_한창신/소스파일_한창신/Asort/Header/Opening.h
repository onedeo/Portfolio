#pragma once
#include "CObject.h"

class CTexture;
class CSound;

#define PokemonQuant 16

class Opening :
    public CObject
{
private:
    Point pPokemonOriginalCenter;
    Point pPokemonCenter;
    Point pAshCenter;
    Point pLogoCenter;
    Point pTempCenter;

    Point pPokemonScale[PokemonQuant];
    Point pAshScale;
    Point pLogoScale;
    Point pTempScale;

    bool bSwitch;
    int iPokemon;
    float fAccum;
    float fSpeed;
    Vec2 vDir;

    CTexture* texPokemon[PokemonQuant];
    CTexture* texAsh;
    CTexture* texLogo;
    CTexture* texBackground;
    Point pResolution;

    CSound* sndBG;

public:
    Opening();
    ~Opening();

    virtual void Update();
    virtual void Render(HDC _dc);

private:
    void Init();

    void RenderPokemon(HDC _dc);
    void RenderLogo(HDC _dc);
    void RenderAsh(HDC _dc);
    void RenderBG(HDC _dc);

    void OutPokemon();
    void NextPokemon();
};

