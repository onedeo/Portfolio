using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class Inverter : Node
    {
        Transform transform;
        Inverter(Transform transform) : base()
        {
            this.transform = transform;
        }
        public override NodeState Evaluate()
        {
            if (children.Count != 1)
            {
                Debug.Log(transform.name + "Inverter Node Has No or More Than 1 Child");
                return NodeState.FAILURE;
            }

            switch (children[0].Evaluate())
            {
                case NodeState.RUNNING:
                    return NodeState.RUNNING;
                case NodeState.SUCCESS:
                    return NodeState.FAILURE;
                case NodeState.FAILURE:
                    return NodeState.SUCCESS;
            }
            return NodeState.FAILURE;
        }

    }
}