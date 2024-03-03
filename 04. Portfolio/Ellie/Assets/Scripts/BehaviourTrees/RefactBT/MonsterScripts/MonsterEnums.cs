using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public enum MonsterComponentData
    {
        MONSTER,
        AGENT,
        AUDIO,
        AUDIO_CON,
        TRANSFORM,
        ANIMATOR,
        PATROL_POINTS,
        PARTICLE,
        MONSTER_CENTER,

        PlayerDetectAI,
        ChaseDetectAI,
    }

    public enum BTData
    {
        bOnSpawnPosition,
        bOvertraveld,
        bReturning,

        fPlayerDistanceSqr,
        fSpawnDistanceSqr,

        v3PlayerPosition,

        iCurrentHP,
    }


    public enum MonsterData
    {
        v3SpawnPosition,

        // Datas
        MonsterStat,
        RunToPlayer,
        Melee,
        Weapon,
        Flee,
        Projectile,
    }

    public enum MonsterSkill
    {
        RunToPlayer,
        Melee,
        Projectile,
        Weapon,
        Flee,
    }
  

    public enum DetectType
    {
        PLAYER,
        CHASE,
    }
    public enum AnimationType
    {
        IDLE,
        STANDUP,
        WALK,
        SIT,
        IDLE_ATTACK,
        RUN,
        MELEE,
        WEAPON,
        FLEE,
        PROJECTILE_CAST,
        PROJECTILE_FIRE,
    }
    public enum MonAudioType
    {
        WALK,
    }

    public enum MonsterType
    {
        NormalSkeleton,
        AdventureSekeleton,
        WizardSkeleton,
        GuildguardSkeleton
    }
}
