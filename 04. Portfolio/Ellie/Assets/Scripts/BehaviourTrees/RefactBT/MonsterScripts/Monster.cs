using System.Collections;
using System.Collections.Generic;
using UnityEngine.AI;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class Monster : MonoBehaviour
    {
        public NavMeshAgent agent;

        public MonsterCenter MonsterCenter { get; private set; }
        private DetectAI detectPlayer;
        private DetectAI detectChase;
        private bool isOnSpawnPosition;
        public Transform SpawnTransform { get; private set; }

        [SerializeField]
        public List<Transform> patrolPoints;
        private int patrolIndex;

        public bool DetectedPlayer()
        {
            if (detectPlayer.IsDetected) return true;
            return false;
        }
        public bool DetectedChasePlayer()
        {
            if (detectChase.IsDetected) return true;
            return false;
        }
        public bool GetBoolean(BooleanType type)
        {
            switch (type)
            {
                case BooleanType.ON_SPAWN_POSITION:
                    return isOnSpawnPosition;
            }

            Debug.Log(gameObject.name + "Trying to Access Boolean Does Not Have");
            return false;
        }

        public Transform PatrolToNextPoint()
        {
            return patrolPoints[patrolIndex];
        }
    }
}