using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cloud2D : MonoBehaviour
{
    private float maxSpeed;
    private void Start()
    {
        maxSpeed = Random.Range(200, 300);
        float fScale = Random.Range(0.05f, 0.2f);
        transform.localScale = new Vector3(fScale, fScale, fScale);

        Invoke("SelfDestroy", 10.0f);
    }
    private void Update()
    {
        float x = -1f;
        transform.Translate(transform.right * x * maxSpeed * Time.deltaTime);
    }
    private void SelfDestroy()
    {
        Destroy(gameObject);
    }
}
