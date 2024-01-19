﻿using UnityEngine;
using System.Collections;
using TheKiwiCoder;
using Assets.Scripts.Monsters.Utility;
using Assets.Scripts.Monsters.Others;
using Assets.Scripts.Monsters.AbstractClass;
using UnityEngine.AI;
using Assets.Scripts.UI.Monster;
using Assets.Scripts.Managers;
using Assets.Scripts.Combat;
using Assets.Scripts.StatusEffects;
using static Assets.Scripts.Monsters.Utility.Enums;

namespace Assets.Scripts.Monsters
{
    public class WitchSkeletonController : AbstractMonster, ICombatant
    {
        private enum ParshingSkills
        {
            AOEAttack=2013,
            Flee = 2014,
            FireBall = 2015,
            BoxCollider = 2016,
        }
        protected override void Awake()
        {
            base.Awake();
            behaviourTreeInstance = GetComponent<BehaviourTreeInstance>();
            audioController = GetComponent<MonsterAudioController>();

            SetTicketMachine();
            InitUI();
        }

        private void Start()
        {
            StartCoroutine(InitParsingData());
        }

        private IEnumerator InitParsingData()
        {
            yield return DataManager.Instance.CheckIsParseDone();
            monsterData = DataManager.Instance.GetIndexData<SkeletonMonsterData, SkeletonMonsterDataParsingInfo>(((int)MonsterNumber.CaveWitch));

            SetSkills();
            InitData();
            SetNavMesh();
            SetBehaviourTreeInstance();
        }
        private void SetSkills()
        {
            for (int i = 0; i < (int)AttackSkill.End; i++)
            {
                attackData[i] = null;
            }

            attackData[(int)AttackSkill.AOEAttack] = DataManager.Instance.GetIndexData<MonsterAttackData, MonsterAttackDataparsingInfo>((int)ParshingSkills.AOEAttack);
            attackData[(int)AttackSkill.Flee] = DataManager.Instance.GetIndexData<MonsterAttackData, MonsterAttackDataparsingInfo>((int)ParshingSkills.Flee);
            attackData[(int)AttackSkill.ProjectileAttack] = DataManager.Instance.GetIndexData<MonsterAttackData, MonsterAttackDataparsingInfo>((int)ParshingSkills.FireBall);
            attackData[(int)AttackSkill.BoxCollider] = DataManager.Instance.GetIndexData<MonsterAttackData, MonsterAttackDataparsingInfo>((int)ParshingSkills.BoxCollider);

            for (int i = 0; i < (int)AttackSkill.End; i++)
            {
                MonsterAttackData temp = attackData[i];
                if (temp == null) continue;

                AbstractAttack tempAttack = AddSkills(temp.attackName, temp.attackType);

                switch (temp.attackType)
                {
                    case AttackSkill.RunToPlayer:
                        behaviourTreeInstance.SetBlackboardValue<float>("RunAttackMinimumDistance", temp.attackableDistance);
                        behaviourTreeInstance.SetBlackboardValue<float>("RunAttackInterval", temp.attackInterval);
                        break;
                    case AttackSkill.Flee:
                        behaviourTreeInstance.SetBlackboardValue<float>("ActivatableFleeDistance", temp.attackableDistance);
                        behaviourTreeInstance.SetBlackboardValue<float>("ActivateFleeInterval", temp.attackInterval);
                        behaviourTreeInstance.SetBlackboardValue<float>("FleeDistance", temp.fleeDistance);
                        behaviourTreeInstance.SetBlackboardValue<float>("FleeSpeed", temp.movementSpeed);
                        break;
                    case AttackSkill.BoxCollider:
                        tempAttack.InitializeBoxCollider(temp);
                        behaviourTreeInstance.SetBlackboardValue<float>("MeleeAnimationHold", temp.animationHold);
                        behaviourTreeInstance.SetBlackboardValue<float>("MeleeAttackableDistance", temp.attackableDistance);
                        behaviourTreeInstance.SetBlackboardValue<float>("MeleeAttackInterval", temp.attackInterval);
                        break;
                    case AttackSkill.ProjectileAttack:
                        tempAttack.InitializeProjectile(temp);
                        behaviourTreeInstance.SetBlackboardValue<float>("ProjectimeAnimationHold", temp.animationHold);
                        behaviourTreeInstance.SetBlackboardValue<float>("projectileAttackableDistance", temp.attackableMinimumDistance);
                        behaviourTreeInstance.SetBlackboardValue<float>("ProjectileAttackInterval", temp.attackInterval);
                        break;
                    case AttackSkill.FanshapeAttack:
                        tempAttack.InitializeFanShape(temp);
                        behaviourTreeInstance.SetBlackboardValue<float>("FanshapeAnimationHold", temp.animationHold);
                        behaviourTreeInstance.SetBlackboardValue<float>("FanshpaeAttackableDistance", temp.attackableDistance);
                        behaviourTreeInstance.SetBlackboardValue<float>("FanshpaeAttackInterval", temp.attackInterval);
                        break;
                    case AttackSkill.AOEAttack:
                        tempAttack.InitializeAOE(temp);
                        behaviourTreeInstance.SetBlackboardValue<float>("AOEAnimationHold", temp.animationHold);
                        behaviourTreeInstance.SetBlackboardValue<float>("AOEAttackableDistance", temp.attackableMinimumDistance);
                        behaviourTreeInstance.SetBlackboardValue<float>("AOEAttackInterval", temp.attackInterval);
                        break;
                }
            }
        }

        private void InitData()
        {
            dataContainer.MaxHp = (int)monsterData.maxHP;
            currentHP = monsterData.maxHP;
            dataContainer.PrevHp = (int)currentHP;
            dataContainer.CurrentHp.Value = (int)currentHP;
            dataContainer.Name = monsterData.monsterName;

            billboard.InitData(dataContainer);
        }

        private void SetBehaviourTreeInstance()
        {
            //Temp
            behaviourTreeInstance.SetBlackboardValue<GameObject>("Player", player);
            //<<

            GameObject obj = Functions.FindChildByName(gameObject, "ChasePlayer");
            behaviourTreeInstance.SetBlackboardValue<GameObject>("DetectChaseAI", obj);
            obj.GetComponent<DistanceDetectedAI>().SetDetectDistance(monsterData.chasePlayerDistance);

            obj = Functions.FindChildByName(gameObject, "PlayerDetect");
            behaviourTreeInstance.SetBlackboardValue<GameObject>("DetectPlayerAI", obj);
            obj.GetComponent<DistanceDetectedAI>().SetDetectDistance(monsterData.detectPlayerDistance);

            obj = Functions.FindChildByName(gameObject, "PatrolPoints");
            behaviourTreeInstance.SetBlackboardValue<GameObject>("PatrolPoints", obj);
            obj.SetActive(false);

            spawnPosition = gameObject.transform.position;
            behaviourTreeInstance.SetBlackboardValue<Vector3>("SpawnPosition", spawnPosition);
            behaviourTreeInstance.SetBlackboardValue<float>("MovementSpeed", monsterData.movementSpeed);
            isDead = behaviourTreeInstance.FindBlackboardKey<bool>("IsDead");
            isDamaged = behaviourTreeInstance.FindBlackboardKey<bool>("IsDamaged");
            isReturning = behaviourTreeInstance.FindBlackboardKey<bool>("IsReturning");
            isDead.value = false;
            isDamaged.value = false;
        }

        private void SetNavMesh()
        {
            agent = GetComponent<NavMeshAgent>();
            agent.speed = monsterData.movementSpeed;
            agent.angularSpeed = monsterData.rotationSpeed;
            agent.stoppingDistance = monsterData.stopDistance;
            agent.baseOffset = -0.1f;
        }

        public void ChangeEffectState(StatusEffectName effect)
        {

        }
        public override void ReturnSpawnLocation()
        {
            gameObject.transform.position = spawnPosition;
        }
    }
}

