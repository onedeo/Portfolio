using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class SeqReturnSpawnPosition : Sequence
    {
        SeqReturnSpawnPosition(Transform transform)
        {
            List<Node> children = new();
            Inverter invertBool = new Inverter(new ActionAssertBoolean(transform, BooleanType.ON_SPAWN_POSITION));
            children.Add(invertBool);
            children.Add(new ActionPlayAnimation(transform, AnimationType.WALK));
            children.Add(new ActionPlayAudio(transform, MonAudioType.WALK, true, true));
            children.Add()
        }
    }
}
