using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIGameOver3D : MonoBehaviour
{
    public Text TotalKillCount;
    private void Start()
    {
        TotalKillCount = GameObject.Find("TotalKillCount").GetComponent<Text>();
    }
    private void Update()
    {
        TotalKillCount.text = DataManager3D.GetInstance().GetKillCount().ToString();
    }
}
