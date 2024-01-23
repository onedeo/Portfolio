using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class Inverter : Node
    {
        public Inverter(Node node) : base(node)
        {
        }
        public override NodeState Evaluate()
        {
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