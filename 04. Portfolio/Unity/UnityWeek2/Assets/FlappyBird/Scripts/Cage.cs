using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cage : MonoBehaviour
{
    private FlappyBird player;

    private float fAccum;

    private void Start()
    {
        player = GameObject.Find("FlappyBird").GetComponent<FlappyBird>();
    }
    private void Update()
    {
        if (!GameCenter.GetInstance().bGameStart) return;
        if (fAccum > 6) return;

        transform.Translate(Vector3.down * 5 * Time.deltaTime);
        transform.Translate(Vector3.left * 2 * Time.deltaTime);

        fAccum += Time.deltaTime;

        player.transform.Rotate(Vector3.forward * 10 * Time.deltaTime);

        if (fAccum>2)
        {
            player.ActivateGravity();
        }


    }
}
