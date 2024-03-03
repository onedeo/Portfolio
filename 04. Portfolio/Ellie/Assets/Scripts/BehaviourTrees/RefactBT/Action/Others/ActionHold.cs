using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public class ActionHold : MonsterNode
    {
        private float holdTime;
        private float accumTime=0;
        public ActionHold(float holdTime= 1.0f) : base()
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