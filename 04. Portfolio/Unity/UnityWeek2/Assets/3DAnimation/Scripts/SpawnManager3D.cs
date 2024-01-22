using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnManager3D : MonoBehaviour
{
    private int spawnerCount = 0;
    public Spawner3D spawner;
    private Spawner3D[] totalSpawner;

    private void Start()
    {
        totalSpawner = new Spawner3D[50];
    }
    public void Spawn()
    {
        Spawner3D spawnerObject = Instantiate(spawner);
        totalSpawner[spawnerCount] = spawnerObject;
        spawnerCount++;
    }

    public void DestroyAllSpawners()
    {
        for(int i=0; i<spawnerCount;i++)
        {
            totalSpawner[i].gameObject.SetActive(false);
            Destroy(totalSpawner[i]);
        }
        spawnerCount = 0;
    }


}
