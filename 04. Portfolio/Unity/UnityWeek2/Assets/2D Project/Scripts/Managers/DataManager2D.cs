using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DataManager2D : Singleton<DataManager2D>
{
    private static int playerHP = 5;
    private static int score = 0;

    private void Start()
    {
        EventBus2D.Subscribe(EventBus2DType.ADD_SCORE, AddScore);
        EventBus2D.Subscribe(EventBus2DType.PLAYER_HIT, PlayerDamaged);
    }
    public void PlayerDamaged()
    {
        playerHP--;
        Debug.Log(playerHP);
        if(playerHP < 0)
        {
            EventBus2D.Publish(EventBus2DType.OVER);
        }
    }
    public void AddScore()
    {
        score += 100;
        Debug.Log("UI SCORE : " + score);
    }
    public int GetScore() { return score; }
    public int GetPlayerHP() { return playerHP; }
}
