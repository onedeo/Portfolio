using System.Collections;
using System.Collections.Generic;
using UnityEngine;


using UnityEngine.SceneManagement;

public class GameManagerSL : Singleton<GameManagerSL>
{
    public string nextSceneName="";
    /*
    private static GameManagerSL instance;

    public static GameManagerSL Instance
    {
        get
        {
            if(instance == null)
            {
                instance = FindObjectOfType<GameManagerSL>();
                if(instance==null)
                {
                    GameObject Obj = new GameObject();
                    Obj.name = typeof(GameManagerSL).Name;
                    instance = Obj.AddComponent<GameManagerSL>();
                }
            }

            return instance;
        }
    }
    private void Awake()
    {
        if(instance!=null)
        {
            instance = this as GameManagerSL;
        }
            DontDestroyOnLoad(gameObject);
    }
    */
}
