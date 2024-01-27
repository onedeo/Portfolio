using UnityEngine;
using UnityEngine.AI;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class ActionSetAgent : Node
    {
        //using 제거 (성능차이 있음)
        private MonsterAgent destination;
        NavMeshAgent agent;

        public ActionSetAgent(Transform transform, MonsterAgent destination)
        {
            if (agent == null)
                agent = transform.GetComponent<NavMeshAgent>();
            if (monster == null)
                monster = transform.GetComponent<Monster>();

            this.destination = destination;
        }

        public override NodeState Evaluate()
        {
            if (agent == null) return NodeState.FAILURE;

            switch (destination)
            {
                case MonsterAgent.PLAYER:
                    agent.destination = monster.MonsterCenter.Player.position;
                    break;
                case MonsterAgent.SPAWNPOSITION:
                    agent.destination = monster.SpawnTransform.position;
                    break;
                case MonsterAgent.PATROL:
                    agent.destination = monster.PatrolToNextPoint().position;
                    break;
            }
            return NodeState.SUCCESS;
        }


    }
}