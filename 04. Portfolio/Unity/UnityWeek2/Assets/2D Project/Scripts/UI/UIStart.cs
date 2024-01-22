using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIStart : MonoBehaviour
{
    private void Awake()
    {
        EventBus2D.Subscribe(EventBus2DType.START, ActivateUI);
    }
    void NameEntered()
    {
        EventBus2D.Publish(EventBus2DType.PLAY);
        gameObject.SetActive(false);
    }
    void ActivateUI()
    {
        gameObject.SetActive(true);
    }
}
