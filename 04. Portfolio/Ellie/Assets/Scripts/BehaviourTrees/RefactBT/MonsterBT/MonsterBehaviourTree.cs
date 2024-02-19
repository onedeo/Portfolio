using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class MonsterBehaviourTree : Tree
    {
        protected static Dictionary<MonsterData, object> monsterData = new();

        private MonsterBehaviourTree()
        {
            NavMeshAgent agent = GetComponent<NavMeshAgent>();
            monsterData.Add(MonsterData.AGENT, agent);

            Monster monster = GetComponent<Monster>();
            monsterData.Add(MonsterData.MONSTER, monster);

            AudioSource audioSource = GetComponent<AudioSource>();
            monsterData.Add(MonsterData.AUDIO, audioSource);

            MonsterAudioController audioController = GetComponent<MonsterAudioController>();
            monsterData.Add(MonsterData.AUDIO_CON, audioController);

            Transform transform = GetComponent<Transform>();
            monsterData.Add(MonsterData.TRANSFORM, transform);

            Animator animator = GetComponent<Animator>();
            monsterData.Add(MonsterData.ANIMATOR, animator);

            Transform patrolPoints = transform.Find("PatrolPoints");
            monsterData.Add(MonsterData.PATROL_POINTS, patrolPoints);

            DetectAI detectPlayer = transform.Find("DetectPlayerAI").GetComponent<DetectAI>();
            monsterData.Add(MonsterData.PlayerDetectAI, detectPlayer);

            DetectAI detectChase = transform.Find("DetectChaseAI").GetComponent<DetectAI>();
            monsterData.Add(MonsterData.ChaseDetectAI, detectChase);
        }

        public T GetData<T>(MonsterData data)
        {
            object obj=null;
            if (monsterData.TryGetValue(data, out obj))
            {
                if (obj is T) return (T)obj;
            }
            else
            {
                Debug.Log("Trying To Get Type Does Not Match : "+data.ToString());
                return default(T);
            }

            Debug.Log(gameObject.name + "Has No Object Try to Get : " + data.ToString());
            return default(T);
        }

        protected override Node SetupTree()
        {
            Node root = new Select(new List<Node>
            {
                // TO DO : add composite nodes execute first
            });

            return root;
        }
    }

}