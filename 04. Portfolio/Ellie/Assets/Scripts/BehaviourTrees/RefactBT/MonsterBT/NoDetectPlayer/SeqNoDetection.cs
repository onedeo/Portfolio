using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class SeqNoDetection : Sequence
    {
        public SeqNoDetection(Transform transform)
        {
            List<Node> children = new();
            children.Add(new Hold());
            children.Add(new ActionDetect(transform, DetectType.PLAYER));
            children.Add(new FirstTimeDetectPlayer());
            children.Add(new ActionPlayAnimation(transform, AnimationType.STANDUP));
            children.Add(new Hold(4.0f));
            
            SetChildren(children);
        }
    }
}