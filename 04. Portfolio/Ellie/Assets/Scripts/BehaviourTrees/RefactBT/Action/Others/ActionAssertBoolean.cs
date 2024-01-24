using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class ActionAssertBoolean : Node
    {
        private BooleanType type;
        public ActionAssertBoolean(Transform transform, BooleanType type)
        {
            monster = transform.GetComponent<Monster>();
            this.type = type;
        }

        public override NodeState Evaluate()
        {
            if (monster.GetBoolean(type)) return NodeState.SUCCESS;
            else return NodeState.FAILURE;
        }

    }
}
