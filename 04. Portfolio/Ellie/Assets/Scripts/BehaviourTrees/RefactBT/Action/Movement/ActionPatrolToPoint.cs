using UnityEngine;
using UnityEngine.AI;

namespace Scripts.BehaviourTrees.Monster
{
    public class ActionPatrolToPoint : MonsterNode
    {
        NavMeshAgent agent;
        Vector3[] patrolPoints;
        private int patrolNum;
        private int patrolQuant;

        public ActionPatrolToPoint()
        {
            if (patrolPoints == null)
                patrolPoints = tree.GetComponentData<Vector3[]>(MonsterComponentData.PATROL_POINTS);
            if (patrolPoints == null)
                DebugNull(transform, MonsterComponentData.PATROL_POINTS);

            if (agent == null)
                agent = tree.GetComponentData<NavMeshAgent>(MonsterComponentData.AGENT);
            if (agent == null)
                DebugNull(transform, MonsterComponentData.AGENT);

            patrolQuant = patrolPoints.Length;
            patrolNum = 0;
        }
        public override NodeState Evaluate()
        {
            agent.destination = patrolPoints[patrolNum];
            float distance = Vector3.SqrMagnitude(transform.position - patrolPoints[patrolNum]);

            if(distance<0.1f)
            {
                patrolNum++;
                if (patrolNum == patrolQuant)
                    patrolNum = 0;

                return NodeState.SUCCESS;
            }

            return NodeState.RUNNING;
        }

    }
}