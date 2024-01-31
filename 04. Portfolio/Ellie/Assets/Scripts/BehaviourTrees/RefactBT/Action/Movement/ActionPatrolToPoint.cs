using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class ActionPatrolToPoint : MonsterNode
    {
        public ActionPatrolToPoint(Transform transform)
        {
            if (monster == null)
                monster = transform.GetComponent<Monster>();
        }

        public override NodeState Evaluate()
        {
            if(monster ==null)
            {
                Debug.Log(transform.name + "Has No Monster Component");
                return NodeState.FAILURE;
            }
            
        }
    }
}