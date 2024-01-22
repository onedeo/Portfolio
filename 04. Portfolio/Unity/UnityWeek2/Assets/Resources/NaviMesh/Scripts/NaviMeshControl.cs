using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

/*
 * 데이터 저장/로드
 * 유저 pc에 데이터 저장 (저장 용량 한계가 있음)->레지스터리에 저장
 * 
 * 
 */


public class NaviMeshControl : MonoBehaviour
{
    enum Direction { Right, Left, Front, Back,End}

    private AudioSource audioSource = null;
    public AudioClip[] audioClip = null;

    private NavMeshAgent agent;
    private Rigidbody rb;

    private GameObject arrow;
    private GameObject item;
    private Vector3 itemDirection;

    private Vector3 direction;
    private Collider swordCollider;
    
    private Camera camera;
    private Renderer lastHitRenderer;
        
   private Ray ray;
   private RaycastHit rayHit;


    enum Weapon { Sword, Bow, NONE };

    private int PlayerHP = 3;

    private float runSpeed = 5f;
    private float rotationSpeed = 720f;

    Animator animator;
    bool attacking;

    Weapon crntWeapon;

    public GameObject Sword;
    public GameObject SwordOnBow;

    public GameObject Bow;
    public GameObject BowOnSword;

    private void Start()
    {
        animator = GetComponent<Animator>();
        crntWeapon = Weapon.NONE;
        WeaponToSword();

        agent = GetComponentInChildren<NavMeshAgent>();
        rb = GetComponent<Rigidbody>();
        arrow = GameObject.Find("Arrow");
        item = GameObject.Find("Item");
        swordCollider = Sword.GetComponent<Collider>();
        swordCollider.enabled = false;

        audioSource = GetComponent<AudioSource>();

        //audioClip[0] = Resources.Load(string.Format("NaviMesh/Sounds/foot/{0}", "army")) as AudioClip;

        camera = GetComponentInChildren<Camera>();
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.LeftShift))
            Damaged();
        if (Input.GetKeyDown(KeyCode.Alpha1))
            WeaponToSword();
        if (Input.GetKeyDown(KeyCode.Alpha2))
            WeaponToBow();
        if (Input.GetMouseButtonDown(0) && !attacking)
        {
            PlaySound(audioClip[1]);
            Attack();
        }
        if (Input.GetKeyDown(KeyCode.Space))
        {
            animator.SetTrigger("BowAttackEnd");
        }

        InputAnimation();
        CameraRayHit();
    }
    private void CameraRayHit()
    {
        ray.origin = camera.transform.position;
        ray.direction = camera.transform.forward;
        if (Physics.Raycast(ray.origin,ray.direction, out rayHit,2.0f))
        {
            if (rayHit.collider.gameObject.layer == LayerMask.NameToLayer("Wall"))
            {
                GameObject hitObject = rayHit.collider.gameObject;
                Renderer newHitRenderer = hitObject.GetComponent<Renderer>();
                if(newHitRenderer!=null&&newHitRenderer!=lastHitRenderer)
                {
                    newHitRenderer.enabled = false;
                    if(lastHitRenderer!=null)
                    {
                        lastHitRenderer.enabled = true;
                    }
                    lastHitRenderer = newHitRenderer;
                }
            }
            else
            {
                if(lastHitRenderer!=null)
                {
                    lastHitRenderer.enabled = true;
                    lastHitRenderer = null;
                }
            }        
        }
    }

    private void OnDrawGizmos()
    {
        Gizmos.color = Color.blue;
        Gizmos.DrawLine(ray.origin, ray.direction * 2f + ray.origin);
    }
    private void FixedUpdate()
    {
        CharacterController_Slerp();
        //NavMeshController();
        CharacterRotate();
        PointArrow();
    }

    private void PointArrow()
    {
        itemDirection = item.transform.position - transform.position;
        itemDirection.y = 0f;
        arrow.transform.LookAt(transform.position + itemDirection);
    }

    private void CharacterRotate()
    {
        Quaternion newRot = transform.rotation * Quaternion.Euler(new Vector3(0, Input.GetAxis("Mouse X"), 0) * rotationSpeed * Time.deltaTime);
        rb.MoveRotation(newRot);
    }
    /*
    private void NavMeshController()
    {
        if(Input.GetMouseButtonDown(1))
        {
            Ray ray = camera.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;
            if(Physics.Raycast(ray, out hit))
            {
                agent.SetDestination(hit.point);
            }
            Debug.Log(hit.point);
            
        }
    }
    */

    private void CharacterController_Slerp()
    {
        direction = new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical"));
        float x = Input.GetAxis("Horizontal");
        float y = Input.GetAxis("Vertical");

        rb.MovePosition(rb.transform.position + (transform.forward * y + transform.right * x) * runSpeed * Time.deltaTime);
        animator.SetFloat("Speed", direction.magnitude);

        if (direction.magnitude > 0)
            PlaySound(audioClip[0]);
        else
            StopSound();
    }
    private void PlaySound(AudioClip clip)
    {
        if (audioSource.isPlaying) return;

        audioSource.PlayOneShot(clip);
    }
    private void StopSound()
    {
        audioSource.Stop();
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
            swordCollider.enabled = true;
            animator.SetTrigger("SwordAttack");
            Invoke("StopAttack", 0.5f);
            
        }
        else if (crntWeapon == Weapon.Bow)
        {
            animator.SetTrigger("BowAttack");
            
        }
    }
    private void StopAttack()
    {
        swordCollider.enabled = false;
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
