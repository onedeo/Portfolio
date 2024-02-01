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
        public Vector3 SpawnPosition { get; private set; }

        private DetectAI detectPlayer;
        private DetectAI detectChase;

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
        //public Transform PatrolToNextPoint()
        //    return patrolPoints[patrolIndex];
        //}
    }
}