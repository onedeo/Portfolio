using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class ActionPatrolToPoint : Node
    {
        public ActionPatrolToPoint(Transform transform)
        {
            if (monster == null)
                monster = transform.GetComponent<Monster>();
        }
    }
}