using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RefillRock : MonoBehaviour
{
    private BoxCollider collider;

    private void Awake()
    {
        collider = GetComponent<BoxCollider>();
    }

    private void OnTriggerEnter(Collider other)
    {
        ICollectItem interactable = other.GetComponent<ICollectItem>();
        if (interactable != null)
        {
            interactable.Interact();
            OnCollected();
        }
    }

    private void OnCollected()
    {
        transform.localScale = Vector3.zero;
    }
}
