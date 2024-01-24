using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public enum DetectType
    {
        PLAYER,
        CHASE,
    }
    public enum AnimationType
    {
        STANDUP,
        WALK,

    }
    public enum BooleanType
    {
        ON_SPAWN_POSITION,
    }
    public enum MonAudioType
    {
        WALK,
    }

    public enum MonsterAgent
    {
        PLAYER,
        SPAWNPOSITION,
        PATROL,
    }
}
