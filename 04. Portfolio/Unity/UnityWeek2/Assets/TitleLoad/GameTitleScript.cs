using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.SceneManagement;

public class GameTitleScript : MonoBehaviour
{
    
    private void GoNextScene()
    {
        GameManagerSL.GetInstance().nextSceneName = "NaviMesh";
        SceneManager.LoadScene("Loading");
    }
}
