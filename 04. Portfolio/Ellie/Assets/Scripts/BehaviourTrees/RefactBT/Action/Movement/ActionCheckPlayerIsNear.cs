namespace Scripts.BehaviourTrees.Monster
{
    public class ActionCheckPlayerIsNear : MonsterNode
    {
        public override NodeState Evaluate()
        {
            float playerDistance = tree.GetBTData<float>(BTData.fPlayerDistanceSqr);
            float playerStopDistance = tree.GetMonsterData<MonsterStatData>(MonsterData.MonsterStat).stopDistance;

            if (playerDistance < playerStopDistance)
                return NodeState.SUCCESS;

            return NodeState.FAILURE;
        }
    }
}
