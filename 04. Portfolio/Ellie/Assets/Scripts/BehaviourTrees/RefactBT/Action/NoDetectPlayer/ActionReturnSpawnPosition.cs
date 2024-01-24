using System.Collections;
using System.Collections.Generic;
using UnityEngine.AI;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class ActionReturnSpawnPosition : Node
    {
        private MonsterAgent destination;
        NavMeshAgent agent;

        public ActionReturnSpawnPosition(Transform transform)
        {
            if (agent == null)
                agent = transform.GetComponent<NavMeshAgent>();
            if (monster == null)
                monster = transform.GetComponent<Monster>();
        }
        public override NodeState Evaluate()
        {
            if (agent == null) return NodeState.FAILURE;

            if (monster.GetBoolean(BooleanType.ON_SPAWN_POSITION)) return NodeState.SUCCESS;
            else return NodeState.RUNNING;
        }
    }
}
