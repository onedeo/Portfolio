using UnityEngine;
using UnityEngine.AI;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class ActionSetAgent : MonsterNode
    {
        private MonsterAgent destination;

        public ActionSetAgent(MonsterAgent destination)
        {
            if (agent == null)
                agent = transform.GetComponent<NavMeshAgent>();
            if (agent == null)
            {
                string name = tree.GetData<Transform>(MonsterData.TRANSFORM).name;
                Debug.Log("Try To Access NavMeshAgent That Does Not Have : " + name);
            }

            if (monster == null)
                monster = transform.GetComponent<Monster>();
            if (monster == null)
            {
                string name = tree.GetData<Transform>(MonsterData.TRANSFORM).name;
                Debug.Log("Try To Access Monster That Does Not Have : " + name);
            }

            this.destination = destination;
        }

        public override NodeState Evaluate()
        {
            switch (destination)
            {
                case MonsterAgent.PLAYER:
                    agent.destination = monster.MonsterCenter.Player.position;
                    break;
                case MonsterAgent.SPAWNPOSITION:
                    agent.destination = monster.SpawnPosition;
                    break;
                case MonsterAgent.PATROL:
                    //agent.destination = monster.PatrolToNextPoint().position;
                    break;
            }
            return NodeState.SUCCESS;
        }


    }
}