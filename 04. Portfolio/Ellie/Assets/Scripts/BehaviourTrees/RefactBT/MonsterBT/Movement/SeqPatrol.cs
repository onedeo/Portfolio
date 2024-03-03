using System.Collections.Generic;

namespace Scripts.BehaviourTrees.Monster
{
    public class SeqPatrol : Sequence
    {
        public SeqPatrol()
        {
            List<Node> children = new()
            {
                new ActionDetect(DetectType.PLAYER),
                new ActionPlayAudio(MonsterAudioType.Move1),
                new ActionPlayAnimation(AnimationType.WALK),
                new ActionPatrolToPoint(),
                new ActionPlayAnimation(AnimationType.IDLE),
                new ActionHold(1.0f),
            };

            SetChildren(children);
        }

    }
}