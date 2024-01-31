using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class MonsterNode : Node
    {
        protected MonsterBehaviourTree tree;
        protected Monster monster;
        protected NavMeshAgent agent;
        protected AudioSource audioSource;
        protected MonsterAudioController audioController;
        protected Transform transform;
        protected Animator animator;

        public MonsterNode() : base() { }
        public MonsterNode(List<Node> children) : base(children) { }
    }
}
