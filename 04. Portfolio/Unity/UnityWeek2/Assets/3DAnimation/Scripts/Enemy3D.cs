using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy3D : MonoBehaviour
{
    Animation spartanKing;
    public GameObject objSword = null;

    private float fSpeed=10;
    private bool bRun;
    private bool bAttack;
    private float fAttackTime = 0;
    private bool bDead;

    public GameObject uiObj;

    private void Start()
    {
        spartanKing = gameObject.GetComponentInChildren<Animation>();
        objSword.SetActive(false);

        onSpawn();
    }

    private void FixedUpdate()
    {
        if (bDead) return;
        if (!GameCenter3D.GetInstance().GetGamePlaying()) Destroy(gameObject);
        if (bRun)
            RunToTarget();
        if(bAttack)
        {
            fAttackTime += Time.deltaTime;
            if(fAttackTime>1)
            {
                fAttackTime = 0;
                DataManager3D.GetInstance().SubDefenceHP();
            }
        }
    }

    private void onSpawn()
    {
        if (bDead) return;

        spartanKing.Play("victory");
        bRun = false;
        Invoke("StartRun", 2f);
        
    }

    private void StartRun()
    {
        if (bDead) return;

        spartanKing.wrapMode = WrapMode.Loop;
        spartanKing.Play("charge");
        bRun = true; 
    }

    private void RunToTarget()
    {
        transform.LookAt(new Vector3(0, transform.position.y, 0));
        transform.Translate(Vector3.forward * fSpeed * Time.deltaTime);
    }

    private void OnTriggerEnter(Collider other)
    {
        if (!bDead)
        {
            if (other.tag == "Sword")
            {
                bDead = true;
                onDestroy();
            }
            if (other.tag == "Defence")
            {
                bRun = false;
            }
        }
    }

    private void onDestroy()
    {
        DataManager3D.GetInstance().AddKillCount();
        spartanKing.wrapMode = WrapMode.Once;
        spartanKing.Play("diehard");
        uiObj.gameObject.SetActive(false);
        bAttack = false;
        bRun = false;
        Destroy(gameObject, 4.0f);
    }

    private void OnTriggerStay(Collider other)
    {
        if (!bDead)
        {
            if (other.tag == "Defence")
                StartCoroutine(AttackTarget());
            if (!bAttack) bAttack = true;
        }
    }

    private IEnumerator AttackTarget()
    {
        while(true)
        {
            if (bDead) break;
            spartanKing.wrapMode = WrapMode.Once;
            spartanKing.Play("attack");
            yield return new WaitForSeconds(1f);
        }
    }

}
