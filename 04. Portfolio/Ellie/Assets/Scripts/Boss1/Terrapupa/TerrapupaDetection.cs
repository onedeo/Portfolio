using Sirenix.OdinInspector;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TerrapupaDetection : MonoBehaviour
{
    [SerializeField] private Transform myTerrapupa;

    private void Start()
    {
        if(myTerrapupa == null)
        {
            Debug.LogError($"{transform} �׶�Ǫ�� Ʈ������ ������ �����ϴ�");
        }
    }

    public Transform MyTerrapupa 
    { 
        get { return myTerrapupa; }
    }
}
