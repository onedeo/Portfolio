using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public class SeqChasePlayer : Sequence
    {
        public SeqChasePlayer()
        {
            List<Node> children = new()
            {
            new ActionDetect(DetectType.CHASE),
            new ActionPlayAudio(MonsterAudioType.Move1),
            new ActionPlayAnimation(AnimationType.WALK),
            new ActionSetAgent(tree.GetBTData<Vector3>(BTData.v3PlayerPosition)),
            };

            SetChildren(children);
        }
        
    }
}