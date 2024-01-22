using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*
 * Invoke : ���� �ð��� ������ ���� �߻��ϴ� �̺�Ʈ
 * Object�� ��Ȱ��ȭ�Ǹ� �ڷ�ƾ�� Ȱ���ȵǴ� �ݸ� Invoke�� �ڷ�ƾ�� ��� Ȱ���ȴ�.
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
