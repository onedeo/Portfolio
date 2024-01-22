using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Pool;

public class SpawnerPool : MonoBehaviour
{
    public int maxPoolSize = 10;
    public int defaultCapacity = 10;

    public Spawner3D spawner;
    private IObjectPool<Spawner3D> spawnerPool;
    
    public IObjectPool<Spawner3D> Pool
    {
        get
        {
            if (spawnerPool == null)
                spawnerPool = new ObjectPool<Spawner3D>(
                    CratedPoolItem,
                    OnTakeFromPool,
                    OnReturnedToPool,
                    onDestroyPoolObject,
                    true,
                    defaultCapacity,
                    maxPoolSize);

            return spawnerPool;
        }
    }

    private Spawner3D CratedPoolItem()
    {
        Spawner3D spawnerTemp= GameObject.Instantiate(spawner);

        spawnerTemp.name = "Spawner";
        spawnerTemp.Pool = Pool;

        return spawnerTemp;        
    }
    private void OnReturnedToPool(Spawner3D _spawner)
    {
        _spawner.gameObject.SetActive(false);
    }
    private void OnTakeFromPool(Spawner3D _spawner)
    {
        _spawner.gameObject.SetActive(true);
    }
    private void onDestroyPoolObject(Spawner3D _spawner)
    {
        Destroy(spawner.gameObject);
    }
    private void onSpawn()
    {
        var _spawner= Pool.Get();
        _spawner.onSpawn();
    }


}
