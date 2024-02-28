using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

namespace Scripts.BehaviourTrees.Monster
{
    public class MonsterBehaviourTree : Tree
    {
        protected Dictionary<MonsterComponentData, object> monsterComponentData = new();
        protected Dictionary<BTData, object> BtData = new();
        protected Dictionary<MonsterData, object> monsterData;

        protected MonsterBehaviourTree()
        {
            InitialComponentData();
            InitialBTData();
        }
        protected override void SetupTree(Node root)
        {
            this.root = root;
        }
        // >> : ComponentData
        private void InitialComponentData()
        {
            NavMeshAgent agent = GetComponent<NavMeshAgent>();
            monsterComponentData.Add(MonsterComponentData.AGENT, agent);

            MonsterBase monster = GetComponent<MonsterBase>();
            monsterComponentData.Add(MonsterComponentData.MONSTER, monster);

            MonsterParticleController particle = GetComponent<MonsterParticleController>();
            monsterComponentData.Add(MonsterComponentData.PARTICLE, particle);

            AudioSource audioSource = GetComponent<AudioSource>();
            monsterComponentData.Add(MonsterComponentData.AUDIO, audioSource);

            MonsterAudioController audioController = GetComponent<MonsterAudioController>();
            monsterComponentData.Add(MonsterComponentData.AUDIO_CON, audioController);

            Transform transform = GetComponent<Transform>();
            monsterComponentData.Add(MonsterComponentData.TRANSFORM, transform);

            Animator animator = GetComponent<Animator>();
            monsterComponentData.Add(MonsterComponentData.ANIMATOR, animator);

            Transform patrolPoints = transform.Find("PatrolPoints");
            monsterComponentData.Add(MonsterComponentData.PATROL_POINTS, patrolPoints);

            DetectAI detectPlayer = transform.Find("DetectPlayerAI").GetComponent<DetectAI>();
            monsterComponentData.Add(MonsterComponentData.PlayerDetectAI, detectPlayer);

            DetectAI detectChase = transform.Find("DetectChaseAI").GetComponent<DetectAI>();
            monsterComponentData.Add(MonsterComponentData.ChaseDetectAI, detectChase);

            Vector3[] patorlPoints = transform.Find("PatrolPoints").GetComponent<PatrolPoints>().GetPatrolPointst();
            monsterComponentData.Add(MonsterComponentData.PATROL_POINTS, patrolPoints);
        }
        public T GetComponentData<T>(MonsterComponentData data)
        {
            object obj = null;
            if (monsterComponentData.TryGetValue(data, out obj))
            {
                if (obj is T) return (T)obj;
            }
            else
            {
                Debug.LogFormat("Trying To Get Type Does Not Match : {0}, {1} " + data.ToString(), transform.name);
                return default(T);
            }

            Debug.LogFormat(gameObject.name + "Trying To Access Object Does Not Have : {0}, {1}" + data.ToString(), transform.name);
            return default(T);
        }

        // >> : BTData
        private void InitialBTData()
        {
            SetBTData<bool>(BTData.bOnSpawnPosition, true);
            SetBTData<bool>(BTData.bOvertraveld, false);
            SetBTData<bool>(BTData.bReturning, false);
        }
        public T GetBTData<T>(BTData data)
        {
            object obj;
            if (BtData.TryGetValue(data, out obj))
            {
                if (obj is T) return (T)obj;
                else
                {
                    Debug.LogFormat("Trying To Get Component Does Not Match : {0}, {1} " + data.ToString(), transform.name);
                    return default(T);
                }
            }
            else
            {
                T defaultValue = default(T);
                BtData.Add(data, defaultValue);
                return defaultValue;
            }
        }
        public void SetBTData<T>(BTData data, T value)
        {
            if (BtData.ContainsKey(data))
            {
                if (BtData[data] is T)
                {
                    BtData[data] = value;
                    return;
                }
                else
                {
                    Debug.LogFormat("Trying To Get Data Does Not Match : {0}, {1} " + data.ToString(), transform.name);
                    return;
                }
            }

            Debug.LogFormat("Trying to access data that does not exist: {0}, {1}", data.ToString(), transform.name);
        }

        // >> : MonsterData
        public T GetMonsterData<T>(MonsterData data)
        {
            object obj;
            if (monsterData.TryGetValue(data, out obj))
            {
                if (obj is T) return (T)obj;
                else
                {
                    Debug.LogFormat("Trying To Get Monster Data Does Not Match : {0}, {1} " + data.ToString(), transform.name);
                    return default(T);
                }
            }

            Debug.LogFormat(gameObject.name + "Trying To Access Monster Data Does Not Have : {0}, {1}" + data.ToString(), transform.name);
            return default(T);
        }
        public void AddMonsterData<T>(MonsterData key, T value)
        {
            if(monsterData.ContainsKey(key))
            {
                Debug.LogFormat("{0} Is Trying To Add Key {1} Already Exists : {0}, {1}", transform.name, key.ToString());
                return;
            }
            monsterData.Add(key, value);
        }
    }
}