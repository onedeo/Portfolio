using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spawner : MonoBehaviour
{
    public GameObject wallPrefab;
    private float fInterval;


    private void Start()
    {
            StartCoroutine("StartSpawner");
    }

    private IEnumerator StartSpawner()
    {
        while(true)
        {
            if (GameCenter.GetInstance().bGameStart)
                Instantiate(wallPrefab, transform.position, transform.rotation);

            fInterval = Random.Range(1, 3);
            yield return new WaitForSeconds(fInterval);
        }
    }

    /*
     IEnumerator Start()
    {
        while (true)
        {
            Instantiate(wallPrefab, transform.position, transform.rotation);
            yield return new WaitForSeconds(fInterval);
        }
    }
       */

}
