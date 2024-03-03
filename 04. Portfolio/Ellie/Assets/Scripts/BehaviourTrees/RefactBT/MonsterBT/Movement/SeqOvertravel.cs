using System.Collections.Generic;

namespace Scripts.BehaviourTrees.Monster
{
    public class SeqOvertravel : Sequence
    {
        public SeqOvertravel()
        {
            List<Node> children = new()
            {
                new ActionAssertBoolean(tree.GetBTData<bool>(BTData.bOvertraveld)),
                new ActionPlayAudio(MonsterAudioType.Move1),
                new ActionPlayAnimation(AnimationType.WALK),
                new SeqReturnSpawnPosition(),
                new ActionPlayAnimation(AnimationType.SIT),
                new ActionSetBoolean(BTData.bOnSpawnPosition, true),
                new ActionSetBoolean(BTData.bOvertraveld, false),
            };

            SetChildren(children);
        }
    }
}