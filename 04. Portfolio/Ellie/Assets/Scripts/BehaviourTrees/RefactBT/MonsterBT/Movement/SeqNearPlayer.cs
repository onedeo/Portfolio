using System.Collections.Generic;

namespace Scripts.BehaviourTrees.Monster
{
    public class SeqNearPlayer : Sequence
    {
        public SeqNearPlayer()
        {
            List<Node> children = new()
            {
                new ActionCheckPlayerIsNear(),
                new ActionPlayAudio(MonsterAudioType.IdleAttack1),
                new ActionPlayAnimation(AnimationType.WALK),
                new ActionLookPlayer(),
                new ActionPlayAnimation(AnimationType.IDLE_ATTACK),
            };

            SetChildren(children);
        }
    }
}