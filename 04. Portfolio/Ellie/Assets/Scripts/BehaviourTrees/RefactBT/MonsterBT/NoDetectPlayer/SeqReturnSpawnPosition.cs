using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public class SeqReturnSpawnPosition : Sequence
    {
        public SeqReturnSpawnPosition()
        {     
            List<Node> children = new()
            {
               new Inverter(new ActionAssertBoolean(tree.GetBTData<bool>(BTData.bOnSpawnPosition))),
               new ActionPlayAudio(MonsterAudioType.Move1, true, true),
               new ActionPlayAnimation(AnimationType.WALK),
               new ActionSetAgent(tree.GetMonsterData<Vector3>(MonsterData.v3SpawnPosition)),
               new ActionReturnSpawnPosition(),
               new ActionSetBoolean(BTData.bOnSpawnPosition, true),
            };

            SetChildren(children);
        }
    }
}
