using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class ActionAssertBoolean : MonsterNode
    {
        private bool boolean;
        public ActionAssertBoolean(Transform transform, bool boolean)
        {
            this.boolean = boolean;
        }

        public override NodeState Evaluate()
        {

            if (boolean) return NodeState.SUCCESS;
            else return NodeState.FAILURE;
        }

    }
}
