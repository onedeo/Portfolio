using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy2D : MonoBehaviour
{
    public Missile2D missile;

    private Rigidbody2D rigidBody;
    private float maxSpeed = 1000f;

    private void Start()
    {
        rigidBody = gameObject.GetComponent<Rigidbody2D>();
        StartCoroutine("CreateMissile");
        Invoke("SelfDestroy", 15.0f);
        EventBus2D.Subscribe(EventBus2DType.OVER, SelfDestroy);
    }

    private void Update()
    {
        float x = -1f;

        Vector2 newVec = new Vector2(transform.position.x + x * maxSpeed * Time.deltaTime, transform.position.y);
        rigidBody.MovePosition(newVec);
    }

    int missileCnt;
    private IEnumerator CreateMissile()
    {
        missileCnt = 2;
        while (true)
        {
            if (missileCnt > 0)
            {
                Vector3 missilePos = transform.position;
                missilePos.x -= 100;
                Instantiate(missile, missilePos, transform.rotation);
                yield return new WaitForSeconds(0.5f);
                missileCnt--;
            }
            else
            {
                missileCnt = 5;
                yield return new WaitForSeconds(3f);
            }
        }
    }
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.CompareTag("Player"))
        {
            EventBus2D.Publish(EventBus2DType.PLAYER_HIT);
        }
        if (collision.gameObject.CompareTag("EndOfMap"))
        {
            SelfDestroy();
        }
    }
    private void SelfDestroy()
    {
        Destroy(gameObject);
    }

}
