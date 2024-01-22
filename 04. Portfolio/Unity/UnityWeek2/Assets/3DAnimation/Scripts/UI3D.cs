using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UI3D : MonoBehaviour
{
    private int maxDenominator;
    private Image DefenceHP;
    private Text KillCount;

    private Text title;
    private Button btnStart;
    private UIGameOver3D gameOver;

    private void Start()
    {
        //Default
        maxDenominator = DataManager3D.GetInstance().GetDefenceHP();
        DefenceHP = GameObject.Find("DefenceHP").GetComponent<Image>();
        KillCount = GameObject.Find("KillCount").GetComponent<Text>();

        //Start
        title = GameObject.Find("Title").GetComponent<Text>();
        btnStart = GameObject.Find("StartButton").GetComponent<Button>();

        //GameOver
        gameOver = GameObject.Find("GameOver").GetComponent<UIGameOver3D>();

        gameOver.gameObject.SetActive(false);

    }
    private void Update()
    {
        DefenceHP.fillAmount = (float)DataManager3D.GetInstance().GetDefenceHP() / maxDenominator;
        KillCount.text = DataManager3D.GetInstance().GetKillCount().ToString();
    }

    public void onStartGame()
    {
        title.gameObject.SetActive(false);
        btnStart.gameObject.SetActive(false);
        GameCenter3D.GetInstance().GameStart();
    }

    public void GameOver()
    {

        gameOver.gameObject.SetActive(true);
        gameOver.TotalKillCount = KillCount;
    }

    public void Restartgame()
    {
        gameOver.gameObject.SetActive(false);
        title.gameObject.SetActive(true);
        btnStart.gameObject.SetActive(true);
    }


}
