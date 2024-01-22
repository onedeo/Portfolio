using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Coin : MonoBehaviour
{

    private void Start()
    {
        Invoke("SelfDestroy", 10.0f);
        
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.gameObject.CompareTag("Player"))
        {
            EventBus2D.Publish(EventBus2DType.ADD_SCORE);
            SelfDestroy();
        }
    }

    private void SelfDestroy()
    {
        Destroy(gameObject);
    }
}
