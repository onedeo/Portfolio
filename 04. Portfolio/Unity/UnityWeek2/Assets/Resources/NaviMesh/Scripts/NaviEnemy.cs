using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class NaviEnemy : MonoBehaviour
{
    public GameObject target; //실시간으로 지정할 수 있고, 임의의 오브젝트를 지정할 수 있다.
    NavMeshAgent agent;
    Animator animator;
    

    private void Start()
    {
        agent = GetComponent<NavMeshAgent>();
        animator = GetComponentInChildren<Animator>();
        target = GameObject.Find("NeviMeshPlayer");
    }

    private void Update()
    {
        agent.destination = target.transform.position;
        animator.SetFloat("Speed", agent.speed);
    }


    //private void OnDrawGizmos()
    //{
    //    NavMeshPath path = agent.path;
    //    Gizmos.color = Color.blue;
    //    foreach (Vector3 corner in path.corners)
    //    {
    //        Gizmos.DrawSphere(corner, 0.4f);
    //    }
    //    Gizmos.color = Color.red;
    //    Vector3 pos = transform.position;
    //    foreach(Vector3 corner in path.corners)
    //    {
    //        Gizmos.DrawLine(pos, corner);
    //        pos = corner;
    //    }
    //}

    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.tag=="Sword")
        {
            StartCoroutine("HitByPlayer");
        }

    }

    private void OnTriggerStay(Collider other)
    {
        if (other.gameObject.tag == "Player")
        {
            animator.SetBool("NearPlayer", true);
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if(other.tag=="Player")
        {
            animator.SetBool("NearPlayer", false);
        }
    }

    private IEnumerator HitByPlayer()
    {
        yield return new WaitForSeconds(0.5f);
        animator.SetTrigger("HitByPlayer");
        agent.speed = 0;
        yield return new WaitForSeconds(5.0f);
        animator.SetTrigger("ChasePlayer");
        agent.speed = 2;
    }

}
