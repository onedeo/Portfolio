using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class SeqReturnSpawnPosition : Sequence
    {
        public SeqReturnSpawnPosition(Transform transform)
        {
            List<Node> children = new();
            Inverter invertBool = new Inverter(new ActionAssertBoolean(transform, tree));
            children.Add(invertBool);
            children.Add(new ActionPlayAnimation(transform, AnimationType.WALK));
            children.Add(new ActionPlayAudio(transform, MonsterAudioType.Move1, true, true));
            children.Add(new ActionSetAgent(transform, MonsterAgent.SPAWNPOSITION));
            children.Add(new ActionReturnSpawnPosition(transform));
        }
    }
}
