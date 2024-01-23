using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class ActionReturnToSpawnPosition : Node
    {
        private Monster monster;
        public ActionReturnToSpawnPosition(Transform transform)
        {
            monster = transform.GetComponent<Monster>();
        }
    }
}
