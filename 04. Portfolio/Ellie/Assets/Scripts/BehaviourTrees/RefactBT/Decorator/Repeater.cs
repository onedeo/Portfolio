using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class Repeater : Node
    {
        Transform transform;
        bool repeatOnSuccess;
        bool repeatOnFailure;
        Repeater(Transform transform, List<Node> childrens, bool repeatOnSuccess = true, bool repeatOnFailure = true) : base(childrens)
        {
            this.transform = transform;
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