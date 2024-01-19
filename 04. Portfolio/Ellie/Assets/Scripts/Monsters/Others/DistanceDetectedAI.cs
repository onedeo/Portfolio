using UnityEngine;

namespace Assets.Scripts.Monsters.Others
{

    public class DistanceDetectedAI : MonoBehaviour
    {
        public bool IsDetected { get; private set; }
        private SphereCollider collider;

        private void Awake()
        {
            collider = GetComponent<SphereCollider>();
        }
        public void SetDetectDistance(float playerDetectDistance)
        {
            collider.isTrigger = true;
            collider.radius = playerDetectDistance;
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