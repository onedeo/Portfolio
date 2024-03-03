using System.Collections;
using System.Collections.Generic;
using Assets.Scripts.Player;
using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public class MonsterCenter : MonoBehaviour
    {
        [SerializeField]
        public GameObject Player { get; private set; }
        public float billboardScale { get; private set; }
        public float battleStateTime { get; private set; }
    }
}