using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Missile2D : MonoBehaviour
{
    private float maxSpeed = 1500;
    private Rigidbody2D rigidBody;
    private void Start()
    {
        rigidBody = gameObject.GetComponent<Rigidbody2D>();
        Invoke("SelfDestroy", 10f);

        EventBus2D.Subscribe(EventBus2DType.OVER, SelfDestroy);
    }

    private void Update()
    {
        float x = -1;

        Vector2 newVec = new Vector2(transform.position.x + x * maxSpeed * Time.deltaTime, transform.position.y);
        rigidBody.MovePosition(newVec);
    }
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.CompareTag("Player"))
        {
            EventBus2D.Publish(EventBus2DType.PLAYER_HIT);
        }
        if (collision.gameObject.CompareTag("MissileCut"))
        {
            SelfDestroy();
        }
        if (collision.gameObject.CompareTag("EndOfMap"))
        {
            SelfDestroy();
        }
    }



    void SelfDestroy()
    {
        Destroy(gameObject);
    }
}
