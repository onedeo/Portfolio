using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class MonsterCenter : MonoBehaviour
    {
        [SerializeField]
        public Transform Player { get; private set; }
    }
}