#pragma once
#include "CObject.h"
#include "CTexture.h"
#include <string>
#include <iostream>

enum class AXIS { X, Y, ON_POINT };

class CPokemon;
enum class PLAYER_STATE
{
    ON_OCCUPIED,
    READY_OCG,
    OCCUPYING
    , GOBACK
    , HOLD
    , END
};

class CPlayer :
    public CObject
{
private:
    //Temp
    

    //Stat
    int iLife;

    float fdefaultfSpeed;
    float fSpeed;
    float fRunSpeedRatio;

    float fOCGSpeed; //multiply with fSpeed
    float fRetreatSpeed;
    float fTotSpeed;
    float fCrntSpeed;

    float fStamina;
    float fRecoverStamina;

    Point pCenter;
    Vec2 vCenter;
    Vec2 vScale;
    PLAYER_STATE eState;

    CPokemon* pokemon;

    bool bRecoverStamina;
    bool bSwamp;
    bool bRetreat;
    bool bRunning;

    float fTotalSpeed;

    //OCG
    Point pOCGPoint[500];
    Point OCGDir[(int)DIRECTION::END];
    int ocgCnt;
    bool bCollect; 
    bool OCGonOCD;
    
    //DIRECTIONS
    DIRECTION eDirStart;
    DIRECTION eDirFin;
    DIRECTION eDirBefore;
    DIRECTION eDirCrnt;

    //Movement
    bool moved;
    OCDPoint* ocdNxt;
    OCDPoint* ocdPrv;
    OCDPoint* OCDDir[(int)DIRECTION::END];

    //Render
    CTexture* pTex;

public:
    void CreateMissile();

public:
    virtual void Update();
    virtual void Render(HDC _dc);

private:



public:
    //begining of stage
    virtual void ResetToStart();

    //player finish OCG and set informations

    //get and sets
    OCDPoint* GetOCDVec2();
    PackOCG GetOCGPack();
    DIRECTION GetCrntDirection() { return eDirCrnt; }
    int GetLife() {return iLife; }

    //attacked
    void GoBackOCG0();

    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);

private:

    // >> : Space Key
    void SpaceKeyUpdate();
    // << : Space Key

    // >> : Player Move On States
    void MovementUpdate();
    void MoveOnOCD();
    void MoveReadyOCG();
    void MoveOccupying();
    void MoveGoBack();
    // << : Player Move On States

    // >> : Player On OCG
    void CollectOCGPoints();
    void DeleteOCGPoint();
    void ConfigOCGDir();
    bool IsPlayerOnOCG();
    bool IsOCGExceed(Point center);
    // << : Player On OCG

    // >> : Finish OCG
    bool IsClockwise();
    //void ConfigPackOCG();
    // << : Finish OCG

    void ConfigNxtPrv();
    void ConfigOCDDir();
    void PreventPlayerExceed();
    bool IsPlayerOnOCD();

    void SetSpeed();

    DIRECTION OppositeDirection(DIRECTION _dir);
    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();
    

private:



public:
    CPlayer();
    ~CPlayer();


private:
    //debug
    void PrintState()
    {
        string strState;
        switch (eState)
        {
            case PLAYER_STATE::ON_OCCUPIED:
                strState = "ON_OCCUPIED";
                break;
            case PLAYER_STATE::READY_OCG:
                strState = "READY_OCG";
                break;
            case PLAYER_STATE::OCCUPYING:
                strState = "OCCUPYING";
                break;
            case PLAYER_STATE::GOBACK:
                strState = "GOBACK";
                break;
        }
        cout << "eState: " << strState << '\n';
    }
    void PirntOCDDirection()
    {
        string dir[4] = { "UP: ", "DOWN: ", "RIGHT: ", "LEFT: " };
        for (int i = 0; i < 4; i++)
        {
            if (OCDDir[i] == nullptr)
                dir[i] += "NO";
            else dir[i] += "YES";
            cout << dir[i] << '\n';
        }
    }

    void PrintDirection(DIRECTION _dir)
    {
        string str;
        switch (_dir)
        {
            case DIRECTION::UP:
                str = "UP";
                break;
            case DIRECTION::DOWN:
                str = "DOWN";
                break;
            case DIRECTION::RIGHT:
                str = "RIGHT";
                break;
            case DIRECTION::LEFT:
                str = "LEFT";
                break;
        }
        cout << str;
    }
};

