using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class Sequence : MonsterNode
    {
        public Sequence() : base() { }
        public Sequence(List<Node> childrens) : base(childrens) { }
        public override NodeState Evaluate()
        {
            bool anyChildIsRunning = false;

            foreach(Node child in children)
            {
                switch(child.Evaluate())
                {
                    case NodeState.FAILURE:
                        return NodeState.FAILURE;
                    case NodeState.SUCCESS:
                        return NodeState.SUCCESS;
                    case NodeState.RUNNING:
                        anyChildIsRunning = true;
                        continue;
                    default:
                        return NodeState.SUCCESS;
                }
            }
            return anyChildIsRunning ? NodeState.RUNNING : NodeState.SUCCESS;
        }

    }
}