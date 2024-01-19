using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Scripts.BehaviourTrees.RefactBT
{
    public class Hold : Node
    {
        private float holdTime;
        private float accumTime=0;
        public Hold(float holdTime= 1.0f) : base()
        {
            this.holdTime = holdTime;
        }
        protected override void OnStart()
        {
            accumTime = 0;
        }
        public override NodeState Evaluate()
        {
            if (accumTime >= holdTime) return NodeState.SUCCESS;
            accumTime += Time.deltaTime;
            return NodeState.RUNNING;
        }

    }
}