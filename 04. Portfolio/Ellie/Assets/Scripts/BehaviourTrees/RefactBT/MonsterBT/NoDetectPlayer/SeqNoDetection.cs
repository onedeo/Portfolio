using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class SeqNoDetection : Sequence
    {
        public SeqNoDetection(Transform transform)
        {
            List<Node> children = new()
            {
                new Hold(),
                new ActionDetect(transform, DetectType.PLAYER),
                new ActionPlayAnimation(transform, AnimationType.STANDUP, true),
            };

            SetChildren(children);
        }
    }
}