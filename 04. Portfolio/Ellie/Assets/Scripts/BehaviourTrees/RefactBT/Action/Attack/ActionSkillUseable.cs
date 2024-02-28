using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public class ActionSkillUseable : MonsterNode
    {
        float attackableDistance = 0.0f;
        float interval = 0.0f;
        private float lastTime;

        public ActionSkillUseable(float interval, float attackableDistance)
        {
            this.interval = interval;
            this.attackableDistance = attackableDistance;

            lastTime = 0.0f;
        }
        public override NodeState Evaluate()
        {
            float playerDistanceSqr = tree.GetBTData<float>(BTData.fPlayerDistanceSqr);

            if (playerDistanceSqr > attackableDistance)
                return NodeState.FAILURE;
            if (Time.time - lastTime < interval)
                return NodeState.FAILURE;

            lastTime = Time.time;

            return NodeState.SUCCESS;
        }
    }
}
