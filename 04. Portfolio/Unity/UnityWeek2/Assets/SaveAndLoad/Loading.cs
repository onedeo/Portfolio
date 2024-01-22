using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.SceneManagement;
using UnityEngine.UI;

/*
 * 로딩해야 할게 많을 경우 게임이 멈춰있는것 처럼 보인다.
 */

public class Loading : MonoBehaviour
{
    AsyncOperation async;

    private float loadingbar=0;
    public  Image loadingImage;


    private void Start()
    {
        StartCoroutine(LoadingNextScene(GameManagerSL.GetInstance().nextSceneName));
    }
    private void Update()
    {
        DelayTime();
        loadingbar += Time.deltaTime;
        loadingImage.fillAmount = loadingbar;
    }

    private IEnumerator LoadingNextScene(string _sceneName)
    {
        async = SceneManager.LoadSceneAsync(_sceneName); //scene이 어느정도 로드 되어있는지 확인 0~1까지의 %를 가진다.
        async.allowSceneActivation = false;  //true: 씬이 바로 바뀐다. false: scene을 전환하지 않는다.


        //if 문으로 해도 되지만 정확하게 로딩이 안될 수도 있어서 while문으로 처리한다.
        while(async.progress<0.9f)
        {
            yield return true;
        }

        while(async.progress>=0.9f)
        {
            yield return new WaitForSeconds(0.1f);
            if (delayTime >= 2.0f) //최소 2초는 지연 시켜주자(너무 빨리 로딩이 되면 싱겁자나~
                break;
        }
        async.allowSceneActivation = true;
    }

    float delayTime = 0f;
    private void DelayTime()
    {
        delayTime += Time.deltaTime;
    }
}
