using System.Collections.Generic;
using Channels.Combat;
using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public class MonsterStatData
    {
        public MonsterType monsterType;
        public string name;
        public float HP;
        public float speed;
        public float rotationSpeed;
        public float detectPlayerDist;
        public float detectChaseDist;
        public float overtravelDist;
        public float overtravelReturnSpeed;
        public float stopDistance;
        public float weeknessRatio;
        public float respawnTime;
        public List<int> itemTableNum;
        public Vector3 spawnPosition;
    }
    public class RunToPlayerData
    {
        public float interval;
        public float attackableDistance;
        public float speed;
        public float duration;
        public float stopDistance;
    }
    public class MeleeAttackData
    {
        public CombatType combatType;

        public int damage;
        public float interval;
        public float attackableDistance;
        public float duration;
        public float animationHold;

        public float colliderDuration;
        public Vector3 colliderOffset;
        public Vector3 colliderSize;
    }
    public class WeaponAttackData
    {
        public CombatType combatType;

        public int damage;
        public float interval;
        public float attackableDistance;
        public float duration;
        public float animationHold;

        public float angle;
        public float radius;
    }
    public class FleeSkillData
    {
        public float fleeSpeed;
        public float interval;
        public float attackableDistance;
        public float duration;
        public float fleeDistance;
        public float animationHold;
    }
    public class ProjectileAttackData
    {
        public CombatType combatType;
        public string name;

        public float damage;
        public float interval;
        public float attackableDistance;
        public float duration;
        public float animationHold;
        public float projectileSpeed;
    }
}