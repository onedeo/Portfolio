using System.Collections;
using System.Collections.Generic;
using UnityEngine.AI;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class ActionReturnSpawnPosition : MonsterNode
    {
        private MonsterAgent destination;

        public ActionReturnSpawnPosition(Transform transform)
        {
            if (agent == null)
                agent = transform.GetComponent<NavMeshAgent>();
            if (monster == null)
                monster = transform.GetComponent<Monster>();
        }
        public override NodeState Evaluate()
        {
            if (agent == null)
            {
                Debug.Log(transform.name + "Has No NavMeshAgent");
                return NodeState.FAILURE;
            }
            if (monster == null)
            {
                Debug.Log(transform.name + "Has No Monster Component");
                return NodeState.FAILURE;
            }

            float distance = Vector3.SqrMagnitude(transform.position - monster.SpawnPosition);
            if (distance > 0.5f)
            {
                isOnSpawnPosition = true;
                return NodeState.SUCCESS;
            }
            else return NodeState.RUNNING;
        }
    }
}
