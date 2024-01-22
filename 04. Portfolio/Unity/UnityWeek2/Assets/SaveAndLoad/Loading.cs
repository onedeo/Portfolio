using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.SceneManagement;
using UnityEngine.UI;

/*
 * �ε��ؾ� �Ұ� ���� ��� ������ �����ִ°� ó�� ���δ�.
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
        async = SceneManager.LoadSceneAsync(_sceneName); //scene�� ������� �ε� �Ǿ��ִ��� Ȯ�� 0~1������ %�� ������.
        async.allowSceneActivation = false;  //true: ���� �ٷ� �ٲ��. false: scene�� ��ȯ���� �ʴ´�.


        //if ������ �ص� ������ ��Ȯ�ϰ� �ε��� �ȵ� ���� �־ while������ ó���Ѵ�.
        while(async.progress<0.9f)
        {
            yield return true;
        }

        while(async.progress>=0.9f)
        {
            yield return new WaitForSeconds(0.1f);
            if (delayTime >= 2.0f) //�ּ� 2�ʴ� ���� ��������(�ʹ� ���� �ε��� �Ǹ� �̰��ڳ�~
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
