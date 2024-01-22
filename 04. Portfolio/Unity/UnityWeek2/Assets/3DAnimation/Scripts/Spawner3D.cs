using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Pool;

public class Spawner3D : MonoBehaviour
{
    private float fRotateSpeed = 100;
    private Vector3 vCenter;
    private float fSpawnPeriod = 5;

    public IObjectPool<Spawner3D> Pool { get; set; }

    public Enemy3D enemy;

    private void Start()
    {

    }
    public void onSpawn()
    {
        vCenter = new Vector3(0, transform.position.y, 0);
        transform.position = new Vector3(90, 7, 0);
        fRotateSpeed = 70 + GameCenter3D.GetInstance().GetLevel() * 20;

        StartCoroutine(Spawn());
    }
    private void FixedUpdate()
    {
        transform.RotateAround(vCenter, transform.up, fRotateSpeed * Time.deltaTime);
        transform.LookAt(vCenter);
    }
    IEnumerator Spawn()
    {
        while (true)
        {
            yield return new WaitForSeconds(fSpawnPeriod);
            Instantiate(enemy, transform.position, transform.rotation);
        }
    }
}
