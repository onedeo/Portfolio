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
            new ActionDetect(transform, DetectType.PLAYER);
            new ActionPlayAnimation(transform, AnimationType.WALK);
            new ActionPlayAudio(transform, MonsterAudioType.Move1);
            
        }

    }
}