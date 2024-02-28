using System.Collections;
using System.Collections.Generic;
using Assets.Scripts.Combat;
using Assets.Scripts.Managers;
using Assets.Scripts.Monsters.Utility;
using Assets.Scripts.UI.Monster;
using Assets.Scripts.Utils;
using Channels.Combat;
using Channels.Components;
using Channels.Type;
using UnityEngine;
using UnityEngine.AI;

namespace Scripts.BehaviourTrees.Monster
{
    public class MonsterBase : MonoBehaviour, ICombatant
    {
        private Dictionary<MonsterSkill, MonsterAttackBase> attacks;
        [SerializeField] protected MonsterBehaviourTree tree;
        public MonsterStatData monsterStat;
        protected DetectAI detectPlayer;
        protected DetectAI detectChase;
        [SerializeField] public MonsterCenter MonsterCenter { get; private set; }
        [SerializeField] public List<Transform> patrolPoints;

        private NavMeshAgent agent;
        private MonsterAudioController audioController;
        private Animator animator;

        private TicketMachine ticketMachine;

        private float currentHP;
        private bool isHeadshot;

        private UIMonsterBillboard billboard;
        private Transform billboardObject;
        private bool isBillboardOn;
        private Transform cameraObj;
        private Coroutine battleCoroutine;
        private readonly MonsterDataContainer dataContainer = new();

        private void Awake()
        {
            audioController = GetComponent<MonsterAudioController>();
            animator = GetComponent<Animator>();

            ticketMachine = gameObject.GetOrAddComponent<TicketMachine>();
            ticketMachine.AddTickets(ChannelType.Combat, ChannelType.Monster);

            SetDetectAI();

            tree = GetComponent<MonsterBehaviourTree>();
        }
        protected virtual void Start()
        {
            tree.AddMonsterData<GameObject>(MonsterData.v3SpawnPosition, MonsterCenter.Player);
        }
        private void Update()
        {
            MonsterOnPlayerForward();
        }

        // >> : Set Datas
        protected void SetMonsterData(MonsterStatData data)
        {
            // UI
            currentHP = monsterStat.HP;
            dataContainer.MaxHp = (int)monsterStat.HP;
            dataContainer.PrevHp = (int)monsterStat.HP;
            dataContainer.CurrentHp.Value = (int)currentHP;
            dataContainer.Name = monsterStat.name;

            billboardObject = Functions.FindChildByName(gameObject, "Billboard").transform;
            cameraObj = Camera.main.transform;
            billboard = UIManager.Instance.MakeStatic<UIMonsterBillboard>(billboardObject, UIManager.UIMonsterBillboard);
            HideBillboard();
            billboard.InitBillboard(billboardObject);

            // Agent
            agent.speed = monsterStat.speed;

            billboard.InitData(dataContainer);
        }
        private void SetDetectAI()
        {
            GameObject detectPlayerObj = new GameObject("DetectPlayer");
            detectPlayerObj.transform.SetParent(transform);
            detectPlayerObj.transform.localPosition = Vector3.zero;
            detectPlayerObj.transform.localRotation = Quaternion.Euler(Vector3.zero);
            detectPlayerObj.transform.localScale = Vector3.one;
            detectPlayer = detectPlayerObj.AddComponent<DetectAI>();

            GameObject detectChaseObj = new GameObject("DetectChase");
            detectChaseObj.transform.SetParent(transform);
            detectChaseObj.transform.localPosition = Vector3.zero;
            detectChaseObj.transform.localRotation = Quaternion.Euler(Vector3.zero);
            detectChaseObj.transform.localScale = Vector3.one;
            detectPlayer = detectChaseObj.AddComponent<DetectAI>();
            detectChaseObj.AddComponent<SphereCollider>();
        }
        protected void AddAttack(MonsterSkill skill, MonsterAttackBase attack)
        {
            GameObject attackObj = new GameObject(skill.ToString());
            attackObj.transform.SetParent(transform);
            attackObj.transform.localPosition = Vector3.zero;
            attackObj.transform.localRotation = Quaternion.Euler(Vector3.zero);
            attackObj.transform.localScale = Vector3.one;

            switch (skill)
            {
                case MonsterSkill.Melee:
                    attack = attackObj.AddComponent<MonsterMeleeAttack>();
                    break;
                case MonsterSkill.Projectile:
                    attack = attackObj.AddComponent<MonsterProjectileAttack>();
                    break;
                case MonsterSkill.Weapon:
                    attack = attackObj.AddComponent<MonsterWeaponeAttack>();
                    break;
                case MonsterSkill.Flee:
                    attack = attackObj.AddComponent<MonsterFleeSkill>();
                    break;
            }
            if (attack == null)
            {
                Debug.LogFormat("{0} Failed To Add Skill {1}", transform.name, skill.ToString());
                return;
            }

            attacks.Add(skill, attack);
        }

        // >> : Battles
        public bool ExecuteAttack(MonsterSkill skill)
        {
            MonsterAttackBase attack;
            if (attacks.TryGetValue(skill, out attack))
            {
                attack.ExecuteAttack();
                return true;
            }

            Debug.LogFormat("Trying To Access Attack Does Not Have : {0}, {1}", transform.name, skill.ToString());
            return false;
        }
        public void Attack(IBaseEventPayload payload)
        {
            CombatPayload combatPayload = payload as CombatPayload;
            ticketMachine.SendMessage(ChannelType.Combat, combatPayload);
        }

        public void ReceiveDamage(IBaseEventPayload payload)
        {
            CombatPayload combatPayload = payload as CombatPayload;
            UpdateHP(combatPayload.Damage);   
        }

        // >> : MonsterDamaged or Dead
        private void SetMonsterDead()
        {
            audioController.PlayAudio(MonsterAudioType.Dead);
            if (animator == null)
            {
                animator = GetComponent<Animator>();
            }
            animator.Play("Dead");
            GetComponent<Collider>().enabled = false;
            MonsterPayload monsterPayload = new();
            monsterPayload.RespawnTime = monsterStat.respawnTime;
            monsterPayload.Monster = transform;
            monsterPayload.ItemDrop = monsterStat.itemTableNum;
            ticketMachine.SendMessage(ChannelType.Monster, monsterPayload);
        }
        private void UpdateHP(float damage)
        {
            if (tree.GetBTData<bool>(BTData.bReturning))
                return;
            if (isHeadshot) damage *= monsterStat.weeknessRatio;

            if (battleCoroutine != null) StopCoroutine(battleCoroutine);
            battleCoroutine = StartCoroutine(EndBattleState());

            currentHP -= damage;
            tree.SetBTData<float>(BTData.iCurrentHP, currentHP);

            if (currentHP < 1)
            {
                SetMonsterDead();
                HideBillboard();
                isBillboardOn = false;
            }
            else
            {
                if (isHeadshot)
                    audioController.PlayAudio(MonsterAudioType.HeadShot);
                else audioController.PlayAudio(MonsterAudioType.Hit);
            }

            isHeadshot = false;
        }

        // >> : Billboard
        private IEnumerator EndBattleState()
        {
            yield return new WaitForSeconds(MonsterCenter.battleStateTime);
            HideBillboard();
            isBillboardOn = false;
        }
        private void MonsterOnPlayerForward()
        {
            if (!isBillboardOn) return;

            Vector3 direction = transform.position - cameraObj.position;
            float dot = Vector3.Dot(direction.normalized, cameraObj.forward.normalized);

            if (dot > 0)
                ShowBillboard();
            else
                HideBillboard();
        }
        private void HideBillboard()
        {
            billboardObject.transform.localScale = Vector3.zero;
        }
        private void ShowBillboard()
        {
            billboardObject.transform.localEulerAngles = Vector3.one;
            isBillboardOn = true;
        }
    }
}