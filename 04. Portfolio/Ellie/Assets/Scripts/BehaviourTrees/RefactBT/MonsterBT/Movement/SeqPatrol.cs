using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class SeqPatrol : Sequence
    {
        public SeqPatrol(Transform transform)
        {
            List<Node> children = new();
            children.Add(new ActionDetect(transform, DetectType.PLAYER));
            children.Add(new ActionPlayAnimation(transform, AnimationType.WALK));
            children.Add(new ActionPlayAudio(transform, MonsterAudioType.Move1));
            //children.Add(new ActionPa())
        }

    }
}