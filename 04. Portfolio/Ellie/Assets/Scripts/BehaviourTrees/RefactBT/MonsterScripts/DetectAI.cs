using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class DetectAI : MonoBehaviour
    {
        public bool IsDetected { get; private set; }
        private float PlayerDetectDistance;
        private SphereCollider collider;

        DetectAI(float detectDistance)
        {
            PlayerDetectDistance = detectDistance;
        }

        private void Awake()
        {
            collider = GetComponent<SphereCollider>();
        }
        private void Start()
        {
            collider.isTrigger = true;
        }
        private void OnTriggerStay(Collider other)
        {
            if (other.tag == "Player")
            {
                IsDetected = true;
            }
        }
        private void OnTriggerExit(Collider other)
        {
            if (other.tag == "Player")
            {
                IsDetected = false;
            }
        }
    }

}