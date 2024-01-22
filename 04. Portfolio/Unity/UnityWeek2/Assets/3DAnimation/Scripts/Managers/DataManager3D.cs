using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DataManager3D : Singleton<DataManager3D>
{
    private int iKillCount = 0;
    private int iIncreaseLevel = 0;
    private int iDefenceHP = 100;

    public void AddKillCount()
    {
        iKillCount++;
        iIncreaseLevel++;
        if (iIncreaseLevel == 3)
        {
            iIncreaseLevel = 0;
            GameCenter3D.GetInstance().IncreaseLevel();
        }
    }
    public void SubDefenceHP()
    {
        iDefenceHP--;
        if(iDefenceHP==0)
        {
            GameCenter3D.GetInstance().GameOver();
        }
    }
    public int GetDefenceHP()
    {
        return iDefenceHP;
    }
    public int GetKillCount()
    {
        return iKillCount;
    }

    public void Restart()
    {
        iKillCount = 0;
        iIncreaseLevel = 0;
        iDefenceHP = 100;
    }
    
}
