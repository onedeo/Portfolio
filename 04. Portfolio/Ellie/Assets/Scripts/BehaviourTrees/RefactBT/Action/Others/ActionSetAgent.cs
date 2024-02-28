using UnityEngine;
using UnityEngine.AI;

namespace Scripts.BehaviourTrees.Monster
{
    public class ActionSetAgent : MonsterNode
    {
        private NavMeshAgent agent;
        private Vector3 destination;

        public ActionSetAgent(Vector3 destination)
        {
            agent = tree.GetComponentData<NavMeshAgent>(MonsterComponentData.AGENT);
            if (agent == null)
                DebugNull(transform, MonsterComponentData.AGENT);

            this.destination = destination;
        }
        public override NodeState Evaluate()
        {
            agent.destination = destination;
            return NodeState.SUCCESS;
        }
    }
}