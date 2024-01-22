using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Singleton<T> : MonoBehaviour where T : Component
{
    private static T instance;
    public static T GetInstance()
    {
        if(instance == null)
        {
            Debug.Log("instance is Null");
            instance = FindObjectOfType<T>();
            if(instance == null)
            { 
                GameObject Obj=new GameObject();
                Obj.name = typeof(T).Name;
                instance = Obj.AddComponent<T>();
            }
        }
        return instance;
    }
    private void Awake()
    {
        if(instance!=null)
        {
            instance = this as T;
        }
        DontDestroyOnLoad(gameObject);
    }

}
