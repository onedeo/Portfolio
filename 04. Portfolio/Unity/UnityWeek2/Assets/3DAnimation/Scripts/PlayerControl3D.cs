using System.Collections;
using System.Collections.Generic;
using UnityEngine;
/*
 * GameComponent Character Controller : collider과 유사한 역할, 하지만 물리가 적용되지 않는다. (사용하지 않음)
 * 
 * 
 */
public class PlayerControl3D : MonoBehaviour
{
    Animation spartanKing;

    public AnimationClip idle;
    public AnimationClip run;
    public AnimationClip attack;

    private float runSpeed = 20.0f;
    Vector3 velocity;
    Rigidbody rb;

    private float rotationSpeed = 20;
    public GameObject objSword = null;

    private bool bGamePlaying;

    

    private void Start()
    {
        spartanKing = gameObject.GetComponentInChildren<Animation>();
        rb = GetComponent<Rigidbody>();
        objSword.SetActive(false);
  
    }
    private void Update()
    {
        if (!bGamePlaying) return;

        if (Input.GetMouseButtonDown(0))
            StartCoroutine("AttackToIdle");
        
    }
    private void FixedUpdate()
    {
        if (!bGamePlaying) return;

        MoveForward();
        PlayerRotation();
    }


    private void AnimationPlay_1()
    {
        if (Input.GetKeyDown(KeyCode.F))
            spartanKing.Play("walk");

        if (Input.GetKeyDown(KeyCode.Alpha0))
            spartanKing.Play("idle");

        if (Input.GetKeyDown(KeyCode.Alpha1))
            spartanKing.Play("attack");

        if (Input.GetKeyDown(KeyCode.Alpha2))
            spartanKing.Play("run");

        if (Input.GetKeyDown(KeyCode.Alpha3))
            spartanKing.Play("charge");

        if (Input.GetKeyDown(KeyCode.Alpha4))
            spartanKing.Play("idlebattle");

        if (Input.GetKeyDown(KeyCode.Alpha5))
            spartanKing.Play("resist");

        if (Input.GetKeyDown(KeyCode.Alpha6))
            spartanKing.Play("victory");

        if (Input.GetKeyDown(KeyCode.Alpha7))
            spartanKing.Play("salute");

        if (Input.GetKeyDown(KeyCode.Alpha8))
            spartanKing.Play("die");

        if (Input.GetKeyDown(KeyCode.Alpha9))
            spartanKing.Play("diehard");
    }

    private void AnimationPlay_2()
    {

        if(Input.GetKeyDown(KeyCode.Q))
        {
            spartanKing.wrapMode = WrapMode.Once;
            spartanKing.CrossFade("attack",0.6f);
        }


        if (Input.GetKeyDown(KeyCode.W))
        {
            spartanKing.wrapMode = WrapMode.Loop;
            spartanKing.CrossFade("run",0.6f);
        }

        if (Input.GetKeyDown(KeyCode.E))
        {
            spartanKing.wrapMode = WrapMode.Loop;
            spartanKing.CrossFade("idle", 0.6f);
        }

    }

    private void AnimationPlay_3()
    {
        if (Input.GetKeyDown(KeyCode.Q))
        {
            StartCoroutine("AttackToIdle");
        }


        if (Input.GetKeyDown(KeyCode.W))
        {

        }

        if (Input.GetKeyDown(KeyCode.E))
        {

        }
    }

    private IEnumerator AttackToIdle()
    {
        //만약 특정 애니메이션을 하고 있으면 yield break; (일반 함수의 return과 동일 기능)
        if (spartanKing.IsPlaying("attack") == true) yield break;
        //if (spartanKing["attack"].enabled == true) yield break;


        spartanKing.wrapMode = WrapMode.Once;
        spartanKing.CrossFade(attack.name, 0.3f);
        objSword.SetActive(true);
        float delayTime = spartanKing.GetClip(attack.name).length - 0.3f; //GetClip : animation에 있는 클립 가져오는 함수
        yield return new WaitForSeconds(delayTime);

        objSword.SetActive(false);
        spartanKing.wrapMode = WrapMode.Loop;
        spartanKing.CrossFade(idle.name, 0.3f);
    }

    private void  CharacterControl()
    {
        velocity = new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical"));
        velocity *= runSpeed;
        if(velocity.magnitude>0.5)
        {
            spartanKing.wrapMode = WrapMode.Loop;
            spartanKing.CrossFade(run.name, 0.3f);
            transform.LookAt(transform.position + velocity);
        }
        else
        {
            spartanKing.wrapMode = WrapMode.Loop;
            spartanKing.CrossFade(idle.name, 0.3f);
        }
        //pcControl.Move((velocity+Physics.gravity) * Time.deltaTime);
        //pcControl.SimpleMove(velocity);

    }

    private void CharacterControl_Slerp()
    {
        Vector3 vDirection = new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical"));
        Debug.Log(vDirection);

        if (vDirection.sqrMagnitude>0.01f)
        {
            spartanKing.wrapMode = WrapMode.Loop;
            spartanKing.CrossFade(run.name, 0.3f);
            Vector3 forward = Vector3.Slerp(transform.forward, vDirection, rotationSpeed * Time.deltaTime/Vector3.Angle(transform.forward,vDirection));

            transform.LookAt(transform.position + forward);
        }
        else
        {
            spartanKing.wrapMode = WrapMode.Loop;
            spartanKing.CrossFade(idle.name, 0.3f);
        }
        
        //pcControl.Move((vDirection+ Physics.gravity) * runSpeed * Time.deltaTime);
        //pcControl.SimpleMove(vDirection * runSpeed);
    }

    private void MoveForward()
    {
        if (spartanKing.IsPlaying("attack")) return;
        float y = Input.GetAxis("Vertical");
        float x = Input.GetAxis("Horizontal");

        if (Mathf.Abs(y) + Mathf.Abs(x) < 0.2)
        {
            spartanKing.wrapMode = WrapMode.Loop;
            spartanKing.CrossFade("idle", 0.3f);
        }
        else if (Mathf.Abs(y) + Mathf.Abs(x) > 0.2)
        {
            spartanKing.wrapMode = WrapMode.Loop;
            spartanKing.CrossFade(run.name, 0.3f);
        }
        else
        {
            spartanKing.wrapMode = WrapMode.Loop;
            spartanKing.CrossFade("walk", 0.3f);
        }
        rb.MovePosition(rb.transform.position + (transform.forward * y + transform.right * x) * runSpeed * Time.deltaTime);
        


    }

    private void MoveRight()
    {
        if (spartanKing.IsPlaying("attack")) return;
        float x = Input.GetAxis("Horizontal");

        if (x!=0)
        {
            spartanKing.wrapMode = WrapMode.Loop;
            spartanKing.CrossFade("walk", 0.3f);
        }
        else
        {
            spartanKing.wrapMode = WrapMode.Loop;
            spartanKing.CrossFade(idle.name, 0.3f);
        }
        rb.MovePosition(rb.transform.position + transform.right * x * runSpeed * Time.deltaTime);
    }
    private void PlayerRotation()
    {
        Quaternion newRot = transform.rotation * Quaternion.Euler(new Vector3(0, Input.GetAxis("Mouse X"), 0) * rotationSpeed);
        rb.MoveRotation(newRot);
    }

    public void ChangeGamePlaying()
    {
        bGamePlaying = !bGamePlaying;
    }

    public void GameOver()
    {
        ChangeGamePlaying();
        spartanKing.wrapMode=WrapMode.Once;
        spartanKing.Play("die");
    }

}
