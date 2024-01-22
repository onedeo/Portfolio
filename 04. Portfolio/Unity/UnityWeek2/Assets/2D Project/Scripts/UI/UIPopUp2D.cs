using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIPopUp2D : MonoBehaviour
{
    private Text titleText = null;
    public InputField inputText = null;

    public Toggle toggleBgm = null;

    public GameObject radioGroupObj = null;
    public Toggle[] toggleRadio;

    private void Start()
    {
        titleText = GetComponentInChildren<Text>();
        toggleBgm = GetComponentInChildren<Toggle>();
        titleText.text = "—Í";

        toggleRadio = radioGroupObj.GetComponentsInChildren<Toggle>();

    }

    void OnClickOK()
    {
        titleText.text = "OK CLICKED!";
    }
    void OnClickCancel()
    {
        gameObject.SetActive(false);
    }
    void onTextChanged()
    {
        titleText.text = inputText.text;
    }
    void onEditEnd()
    {
        titleText.text = inputText.text;
    }

    public void onToggleBGM()
    {
        if(toggleBgm.isOn)
        {
            //Debug.Log("BGM is Playing");
        }
        else
        {
            for(int i=0; i<toggleRadio.Length;i++)
            {
                toggleRadio[i].isOn = false;
                Debug.Log(i + "isoff");
            }
        }
    }

    public void onToggleRadio()
    {
        if (toggleRadio[0] == null) return;
        if(toggleRadio[0].isOn)
        {
            Debug.Log("BGM1 is Playing");
        }
        else if(toggleRadio[1].isOn)
        {
            Debug.Log("BGM2 is Playing");
        }

    }


}
