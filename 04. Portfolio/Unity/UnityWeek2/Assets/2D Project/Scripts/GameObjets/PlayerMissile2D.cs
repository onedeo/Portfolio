using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMissile2D : MonoBehaviour
{
    private float maxSpeed = 2000;
    private Rigidbody2D rigidBody;
    private float fAccum = 0;
    public Coin coin;
    private void Start()
    {
        rigidBody = gameObject.GetComponent<Rigidbody2D>();
        Invoke("SelfDestroy", 10f);
    }
    private void Update()
    {
        float x = 1f;
        Vector2 newVec = new Vector2(transform.position.x + x * maxSpeed * Time.deltaTime, transform.position.y);

        rigidBody.MovePosition(newVec);
    }
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.layer==LayerMask.NameToLayer("Enemy"))
        {
            int rand = Random.Range(0, 2);
            {
                if(rand==0)
                {
                    Instantiate(coin, collision.transform.position, collision.transform.rotation);
                }
            }
            Destroy(collision.gameObject);
            Destroy(gameObject);
        }
        if (collision.gameObject.CompareTag("MissileCut"))
        {
            SelfDestroy();
        }
    }



    void SelfDestroy()
    {
        Destroy(gameObject);
    }
}
