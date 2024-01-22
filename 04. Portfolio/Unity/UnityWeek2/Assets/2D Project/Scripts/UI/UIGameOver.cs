using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIGameOver : MonoBehaviour
{
    Text totalScore;
    private void Start()
    {
        EventBus2D.Subscribe(EventBus2DType.OVER, ActivateSelf);
        EventBus2D.Subscribe(EventBus2DType.START, DeactivateSelf);

        totalScore = GameObject.Find("TotalScore").GetComponent<Text>();
    }

    private void ActivateSelf()
    {
        totalScore.text = DataManager2D.GetInstance().GetScore().ToString();
        gameObject.SetActive(true) ;
    }
    private void DeactivateSelf()
    {
        gameObject.SetActive(false);
    }

    public void Restart()
    {
        EventBus2D.Publish(EventBus2DType.START);
    }
}
