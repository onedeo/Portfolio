using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spawner2D : MonoBehaviour
{
    public Cloud2D cloud;
    public Enemy2D enemy;

    private void Start()
    {
        StartCoroutine("SpawnCloud");

        EventBus2D.Subscribe(EventBus2DType.PLAY, StartSpawnEnemy);
        EventBus2D.Subscribe(EventBus2DType.OVER, StopSpawnEnemy);
    }

    private IEnumerator SpawnCloud()
    {
        while(true)
        {
            Vector3 newTransform = transform.position;
            float randPos = Random.Range(255, -255);
            newTransform.y = randPos;
            transform.position = newTransform;
            Instantiate(cloud, transform.position,transform.rotation);
            float SpawnTime = Random.Range(1f, 3f);
            yield return new WaitForSeconds(SpawnTime);
        }
    }
    private IEnumerator SpawnEnemy()
    {
        while(true)
        {
            Vector3 newTransform = transform.position;
            float randPos = Random.Range(255, -255);
            newTransform.y = randPos;
            transform.position = newTransform;
            Instantiate(enemy, transform.position, transform.rotation);
            float SpawnTime = Random.Range(1f, 2f);
            yield return new WaitForSeconds(SpawnTime);
        }
    }
    private void StartSpawnEnemy()
    {
        StartCoroutine("SpawnEnemy");
    }

    private void StopSpawnEnemy()
    {
        StopCoroutine("SpawnEnemy");
    }


}
