using System.Collections;
using System.Collections.Generic;
using UnityEngine;
/*
 * Animation을 동일하게 사용하고 모델을 다르게 하려면 Rig-AnimationType이 동일해야 한다.
 * 
 * 
 * 
 */


public class MecanimControl : MonoBehaviour
{
    enum Weapon { Sword, Bow,NONE};

    private int PlayerHP = 3;

    public float runSpeed = 5f;
    public float rotationSpeed = 360f;

    CharacterController pcController;
    Vector3 direction;

    Animator animator;
    bool attacking;

    Weapon crntWeapon;

    public GameObject Sword;
    public GameObject SwordOnBow;

    public GameObject Bow;
    public GameObject BowOnSword;

    private void Start()
    {
        pcController = GetComponent<CharacterController>();
        animator = GetComponent<Animator>();
        crntWeapon = Weapon.NONE;
        WeaponToSword();
    }

    private void Update()
    {
            CharacterController_Slerp();
        if (Input.GetKeyDown(KeyCode.LeftShift))
            Damaged();
        if (Input.GetKeyDown(KeyCode.Alpha1))
            WeaponToSword();
        if (Input.GetKeyDown(KeyCode.Alpha2))
            WeaponToBow();
        if (Input.GetMouseButtonDown(0) && !attacking)
        {
            Attack();
        }
        if (Input.GetKeyDown(KeyCode.Space))
        {
            animator.SetTrigger("BowAttackEnd");
        }

        InputAnimation();
    }
    private void Damaged()
    {
        PlayerHP--;
        if(PlayerHP>0)
            animator.SetTrigger("Damaged");
        else
        {
            animator.SetTrigger("Death");
            PlayerHP = 3;
        }
    }
    private void Attack()
    {
        if (crntWeapon == Weapon.Sword)
        {
            animator.SetTrigger("SwordAttack");
        }
        else if (crntWeapon == Weapon.Bow)
        {
            animator.SetTrigger("BowAttack");
        }
    }
    private void WeaponToBow()
    {
        if (crntWeapon == Weapon.Bow) return;
        crntWeapon = Weapon.Bow;

        Bow.SetActive(true);
        BowOnSword.SetActive(false);
        
        Sword.SetActive(false);
        SwordOnBow.SetActive(true);
    }
    private void WeaponToSword()
    {
        if (crntWeapon == Weapon.Sword) return;

        animator.SetTrigger("DrawSword");
        crntWeapon = Weapon.Sword;
        Sword.SetActive(true);
        SwordOnBow.SetActive(false);
        
        Bow.SetActive(false);
        BowOnSword.SetActive(true);
    }

    private void CharacterRoll()
    {

    }

    private void InputAnimation()
    {
        /*
        if (Input.GetMouseButtonDown(0))
        {
            animator.SetTrigger("AttackTrigger");
        }
        */
        //if (Input.GetMouseButtonDown(0)&&!attacking)
        //{
        //    attacking = true;
        //    animator.SetBool("Attack", attacking);
        //    StartCoroutine("AttadckRoutine");
        //}
    }


    private void CharacterController_Slerp()
    {
        direction = new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical"));
        if(direction.sqrMagnitude>0.01f)
        {
            Vector3 forward = Vector3.Slerp(transform.forward, direction, rotationSpeed * Time.deltaTime / Vector3.Angle(transform.forward, direction));
            transform.LookAt(transform.position + forward);
        }
        else
        {

        }

        pcController.Move(direction * runSpeed * Time.deltaTime + Physics.gravity * Time.deltaTime);
        animator.SetFloat("Speed", pcController.velocity.magnitude);
    }

    private IEnumerator AttadckRoutine()
    {
        while (true)
        {
            yield return new WaitForSeconds(0);
            if (attacking && animator.GetCurrentAnimatorStateInfo(1).IsName("UpperBody.Attack"))
            {
                if (animator.GetCurrentAnimatorStateInfo(1).normalizedTime >= 0.9f)
                {
                      attacking = false;
                    animator.SetBool("Attack", attacking);
                    break;
                }
            }

        }
    }

}
