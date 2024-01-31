using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public enum MonsterData
    {
        MONSTER,
        AGENT,
        AUDIO,
        AUDIO_CON,
        TRANSFORM,
        ANIMATOR,
        
    }

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
