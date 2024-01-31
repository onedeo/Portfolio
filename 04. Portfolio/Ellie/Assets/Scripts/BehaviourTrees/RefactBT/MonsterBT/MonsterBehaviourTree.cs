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


        }

        public object GetData(MonsterData data)
        {
            object obj;
            if (monsterData.TryGetValue(data, out obj))
                return obj;

            Debug.Log(gameObject.name + "Has No Object Try to Get : " + data.ToString());
            return null;
        }

        protected override Node SetupTree()
        {
            return null;
        }
    }

}