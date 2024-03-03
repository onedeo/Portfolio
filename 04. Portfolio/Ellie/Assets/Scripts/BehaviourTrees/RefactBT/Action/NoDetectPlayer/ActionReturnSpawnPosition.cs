namespace Scripts.BehaviourTrees.Monster
{
    public class ActionReturnSpawnPosition : MonsterNode
    {
        public override NodeState Evaluate()
        {
            float distance = tree.GetBTData<float>(BTData.fSpawnDistanceSqr);

            if (distance > 0.5f)
                return NodeState.SUCCESS;

            else return NodeState.RUNNING;
        }
    }
}
