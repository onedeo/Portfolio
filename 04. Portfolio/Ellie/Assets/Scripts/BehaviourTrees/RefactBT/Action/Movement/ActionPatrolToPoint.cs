using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class ActionPatrolToPoint : MonsterNode
    {
        private int patrolNum;
        public ActionPatrolToPoint()
        {
            patrolNum = 0;

        }

        public override NodeState Evaluate()
        {

            return NodeState.SUCCESS;
        }
    }
}