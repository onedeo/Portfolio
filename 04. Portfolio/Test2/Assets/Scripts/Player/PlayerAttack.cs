using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerAttack : MonoBehaviour, ICollectItem
{
    [SerializeField] private const int rayCount = 7;
    [SerializeField] private const int rayDistance = 8;
    [SerializeField] private const float rayGap = 0.2f;

    [SerializeField] private GameObject[] rocks;
    [SerializeField] private GameObject[] attackRocks;
    [SerializeField] Button attackButton;

    private int attackRockCount;
    private int attackableQuant = 6;

    private void Start()
    {
        UpdateRocks();
        attackButton.onClick.AddListener(Attack);
    }

    private void Attack()
    {
        if (attackableQuant == 0) return;
        Debug.Log("Player Attack");

        //attackableQuant--;

        float min = 10.0f;
        Transform closestEnemey = null;
        for (int i = 0; i < rayCount; i++)
        {
            Vector3 startPosition = transform.position + transform.right * rayGap * (i - rayCount / 2);

            RaycastHit hit;
            if(Physics.Raycast(startPosition, transform.forward, out hit, rayDistance, 1<<(int)Enums.LayerEnum.Enemey))
            {
                if (min > hit.distance)
                {
                    closestEnemey = hit.transform;
                    min = hit.distance;
                }
            }
        }
        Vector3 position = transform.position;
        Vector3 toEnemeyVector = closestEnemey.position - position;

        

        Debug.Log(closestEnemey);

    }

    private void OnDrawGizmos()
    {
        Gizmos.color = Color.red;

        for (int i = 0; i < rayCount; i++)
        {
            Vector3 startPosition = transform.position + transform.right * rayGap * (i - rayCount / 2);

            Gizmos.color = Color.red;
            Gizmos.DrawSphere(startPosition, 0.1f);

            Gizmos.color = Color.blue;
            Vector3 endPoint = startPosition + transform.forward * rayDistance;
            Gizmos.DrawLine(startPosition, endPoint);
        }
    }

    public void Interact()
    {
        Debug.Log("Collected Rock");
        if (attackableQuant < 6)
            attackableQuant += 2;
        else attackableQuant = 6;

        Debug.Log(attackableQuant);
        UpdateRocks();
    }

    

    private void UpdateRocks()
    {
        for (int i = 0; i < attackableQuant / 2; i++)
        {
            rocks[i].active = true;
        }
    }
}
