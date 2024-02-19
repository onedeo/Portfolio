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
            if (agent == null)
            {
                string name = tree.GetData<Transform>(MonsterData.TRANSFORM).name;
                Debug.Log("Try To Access NavMeshAgent That Does Not Have : " + name);
            }

            if (monster == null)
                monster = transform.GetComponent<Monster>();
            if(monster==null)
            {
                string name = tree.GetData<Transform>(MonsterData.TRANSFORM).name;
                Debug.Log("Try To Access Monster That Does Not Have : " + name);
            }
        }
        public override NodeState Evaluate()
        {
            float distance = Vector3.SqrMagnitude(transform.position - monster.SpawnPosition);
            if (distance > 0.5f)
                return NodeState.SUCCESS;

            else return NodeState.RUNNING;
        }
    }
}
