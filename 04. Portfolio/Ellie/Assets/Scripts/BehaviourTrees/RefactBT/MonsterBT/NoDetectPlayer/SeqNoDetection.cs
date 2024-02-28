using System.Collections.Generic;

namespace Scripts.BehaviourTrees.Monster
{
    public class SeqNoDetection : Sequence
    {
        public SeqNoDetection()
        {
            List<Node> children = new()
            {
                // undetected player
                new Inverter(new ActionDetect(DetectType.PLAYER)),
                new ActionPlayAudio(MonsterAudioType.Idle,false, true),
                new ActionPlayAnimation(AnimationType.SIT, true),
                new ActionDetect(DetectType.PLAYER),
                // if detected player
                new ActionSetBoolean(BTData.bOnSpawnPosition, false),
                new ActionPlayAnimation(AnimationType.STANDUP, true),
            };

            SetChildren(children);
        }
    }
}