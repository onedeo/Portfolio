using UnityEngine.AI;

namespace Scripts.BehaviourTrees.Monster
{
    public class ActionStop : MonsterNode
    {
        private NavMeshAgent agent;

        public ActionStop()
        {
            agent = tree.GetComponentData<NavMeshAgent>(MonsterComponentData.AGENT);
        }
        public override NodeState Evaluate()
        {
            agent.destination = transform.position;
            return NodeState.SUCCESS;
        }
    }
}
