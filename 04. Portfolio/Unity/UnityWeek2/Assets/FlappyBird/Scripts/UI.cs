using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class UI : MonoBehaviour
{
    private Button startButton;
    private TextMeshProUGUI title;
    private TextMeshProUGUI Score;

    private float fMin;
    private float fSecond;

    private void Start()
    {
        startButton = GameObject.Find("Start").GetComponent<Button>();
        title = GameObject.Find("Title").GetComponent<TextMeshProUGUI>();
        Score = GameObject.Find("Score").GetComponent<TextMeshProUGUI>();
        Score.gameObject.SetActive(false);
       
    }

    private void FixedUpdate()
    {
        startButton.onClick.AddListener(StartGame);
        if (GameCenter.GetInstance().bGameStart)
        {
            fSecond += Time.deltaTime;
            if (fSecond > 60.0f)
            {
                fSecond = 0;
                fMin++;
            }
            if (Score.IsActive())
            {
                string strSec = fSecond.ToString("0.00");
                Score.text = "TIME : " + fMin + " : " + strSec;
            }
        }
    }

    private void StartGame()
    {
        GameCenter.GetInstance().bGameStart = true;
        GameCenter.GetInstance().bGameOver = false;
        startButton.gameObject.SetActive(false);
        title.gameObject.SetActive(false);
        Score.gameObject.SetActive(true);
        fSecond = 0;
        fMin = 0;
    }

}
