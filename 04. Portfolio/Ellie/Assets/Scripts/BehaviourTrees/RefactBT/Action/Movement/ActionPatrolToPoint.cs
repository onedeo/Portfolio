using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class ActionPatrolToPoint : MonsterNode
    {
        public ActionPatrolToPoint(Transform transform)
        {
            if (monster == null)
                monster = transform.GetComponent<Monster>();
        }
    }
}