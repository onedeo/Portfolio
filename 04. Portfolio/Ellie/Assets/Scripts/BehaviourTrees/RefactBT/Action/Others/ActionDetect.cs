using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class ActionDetect : MonsterNode
    {
        public DetectType type;
        public ActionDetect(Transform transform, DetectType type)
        {
            if (monster == null)
                monster = transform.GetComponent<Monster>();
        }

        public override NodeState Evaluate()
        {
            if (monster == null)
            {
                Debug.Log(transform.name + "Has No Monster Component");
                return NodeState.FAILURE;
            }

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