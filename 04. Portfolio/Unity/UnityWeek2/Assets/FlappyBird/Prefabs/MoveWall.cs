using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*
 * Invoke : 일정 시간이 지나고 나면 발생하는 이벤트
 * Object가 비활성화되면 코루틴이 활성안되는 반면 Invoke는 코루틴이 계속 활성된다.
 * 
 * 
 */

public class MoveWall : MonoBehaviour
{
    private float fMoveSpeed = 5;
    private float fYLocation;

    private Renderer render;

    /*
    IEnumerator Start()
    {
        while(true)
        {
            yield return new WaitForSeconds(3.0f);
            Destroy();
        }
    }
    */

    private void Start()
    {
        fYLocation = Random.Range(-3, 3);
        Vector3 newPos = transform.position;
        newPos.y += fYLocation;
        transform.position = newPos;
        Invoke("Destroy", 10.0f);
    }
    private void FixedUpdate()
    {
        if(GameCenter.GetInstance().bGameStart)
        transform.Translate(Vector3.left * fMoveSpeed * Time.deltaTime);
    }
    private void Destroy()
    {
        DestroyImmediate(gameObject);
    }

    public void ChangeColor()
    {

    }
    private void OnCollisionEnter(Collision collision)
    {
        if(collision.gameObject.CompareTag("Player"))
        {
            render.material.color = Color.red;
        }
    }

}
