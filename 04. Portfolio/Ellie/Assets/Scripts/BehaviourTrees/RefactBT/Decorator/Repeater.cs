using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public class Repeater : Node
    {
        bool repeatOnSuccess;
        bool repeatOnFailure;
        public Repeater(Node child, bool repeatOnSuccess = true, bool repeatOnFailure = true) : base(child)
        {
            this.repeatOnFailure = repeatOnFailure;
            this.repeatOnSuccess = repeatOnSuccess;
        }
        public Repeater(List<Node> childrens, bool repeatOnSuccess = true, bool repeatOnFailure = true) : base(childrens)
        {
            this.repeatOnFailure = repeatOnFailure;
            this.repeatOnSuccess = repeatOnSuccess;
        }
        public override NodeState Evaluate()
        {
            if (children.Count != 1)
            {
                Debug.Log(transform.name + "Repeater Node Has No or More Than 1 Child");
                return NodeState.FAILURE;
            }
            switch (children[0].Evaluate())
            {
                case NodeState.RUNNING:
                    return NodeState.RUNNING;
                case NodeState.SUCCESS:
                    if (repeatOnSuccess) return NodeState.RUNNING;
                    return NodeState.SUCCESS;
                case NodeState.FAILURE:
                    if (repeatOnFailure) return NodeState.FAILURE;
                    return NodeState.FAILURE;
            }

            return NodeState.RUNNING;
        }

    }
}