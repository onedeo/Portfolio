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
                new ActionDetect(DetectType.PLAYER),
                new ActionPlayAnimation(AnimationType.STANDUP, true),
                new ActionPlayAudio(MonsterAudioType.Move1),
                new ActionPatrolToPoint(),
            };

            SetChildren(children);
        }
    }
}