using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameCenter : Singleton<GameCenter>
{
    public bool bGameStart = false;
    public bool bPlayerDead= false;
    public bool bGameOver = false;

    private void Update()
    {
        if (!bGameStart&&!bPlayerDead)
        {
            if (Input.GetKeyDown(KeyCode.Space))
                bGameStart = true;
        }

        if(bGameOver)
        {
            Invoke("OpenNew", 4.0f);
        }

    }
    void OpenNew()
    {
        SceneManager.LoadScene("FlappyBird");
    }

}
