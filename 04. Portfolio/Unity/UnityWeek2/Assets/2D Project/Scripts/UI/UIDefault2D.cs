using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIDefault2D : MonoBehaviour
{
    public GameObject popupObj = null;
    private Text textScore = null;
    public InputField textInput= null;
    private Text textName = null;

    private void Start()
    {
        if(popupObj)
            popupObj.SetActive(false);

        textScore = GameObject.Find("score").GetComponent<Text>();
        textName = GameObject.Find("name").GetComponent<Text>();
        

        EventBus2D.Subscribe(EventBus2DType.ADD_SCORE, UpdateScore);
        textScore.text = "0";

    }
    private void onPopup()
    {
        if (popupObj == null) return;

            if (popupObj.activeSelf)
            popupObj.SetActive(false);
        else
            popupObj.SetActive(true);
    }
    private void UpdateScore()
    {
        textScore.text = DataManager2D.GetInstance().GetScore().ToString();
    }

    public void onNameEditEnd()
    {
        textName.text = textInput.text;
    }
}
