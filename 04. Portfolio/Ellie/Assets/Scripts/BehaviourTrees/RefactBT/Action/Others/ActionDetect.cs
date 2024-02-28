namespace Scripts.BehaviourTrees.Monster
{
    public class ActionDetect : MonsterNode
    {
        private DetectType type;

        public ActionDetect(DetectType type)
        {
            this.type = type;
        }
        public override NodeState Evaluate()
        {
            switch (type)
            {
                case DetectType.PLAYER:
                    if (tree.GetComponentData<DetectAI>(MonsterComponentData.PlayerDetectAI).IsDetected)
                        return NodeState.SUCCESS;
                    break;
                case DetectType.CHASE:
                    if (tree.GetComponentData<DetectAI>(MonsterComponentData.ChaseDetectAI).IsDetected)
                        return NodeState.SUCCESS;
                    break;
            }

            return NodeState.FAILURE;
        }
    }
}