using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FlappyBird : MonoBehaviour
{
    public float jumpPower = 1.0f;
    Rigidbody rigidBody;

    private bool bJumping;
    private float fMaxRotation = 45.0f;

    private float fRotation = 0;

    private void Start()
    {
        rigidBody = gameObject.GetComponent<Rigidbody>();
        rigidBody.useGravity = false;
    }

    private void Update()
    {
        if (rigidBody.useGravity == false || !GameCenter.GetInstance().bGameStart)
            return;


        if (Input.GetKeyDown(KeyCode.Space))
        {
            rigidBody.velocity = new Vector3(0, jumpPower, 0);
            bJumping = true;
        }
        
        if (bJumping)
        {
            if (fRotation < 30)
            {
                float rot = 40 * Time.deltaTime;
                fRotation += rot;
                transform.Rotate(Vector3.forward * rot);
            }
            Invoke("NotJumping", 0.5f);
        }
        else
        {
            if (fRotation > -30)
            {
                float rot = -40 * Time.deltaTime;
                fRotation += rot;
                transform.Rotate(Vector3.forward * rot);
            }
        }
        Debug.Log(fRotation);
    }

    private void NotJumping()
    {
        bJumping = false;
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.layer == LayerMask.NameToLayer("Wall"))
        {
            GameCenter.GetInstance().bGameStart = false;
            GameCenter.GetInstance().bPlayerDead = true;
            GameCenter.GetInstance().bGameOver = true;
        }
    }
    public void ActivateGravity()
    {
        rigidBody.useGravity = true;
    }

}
