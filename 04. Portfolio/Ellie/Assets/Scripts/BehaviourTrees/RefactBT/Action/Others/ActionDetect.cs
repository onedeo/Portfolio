using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class ActionDetect : Node
    {

        public DetectType type;
        private Monster monster;
        public ActionDetect(Transform transform, DetectType type)
        {
            monster = transform.GetComponent<Monster>();
            if (monster == null) Debug.Log(transform.name + "Has No Monster Component");
        }

        public override NodeState Evaluate()
        {
            switch (type)
            {
                case DetectType.PLAYER:
                    if (monster.DetectedPlayer())
                        return NodeState.SUCCESS;
                    break;
                case DetectType.CHASE:
                    if (monster.DetectedChasePlayer())
                        return NodeState.SUCCESS;
                    break;
            }
            return NodeState.FAILURE;
        }

    }
}