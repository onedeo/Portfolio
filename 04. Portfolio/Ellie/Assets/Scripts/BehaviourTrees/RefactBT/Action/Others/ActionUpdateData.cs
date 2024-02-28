using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public class ActionUpdateData : MonsterNode
    {
        public ActionUpdateData() { }

        public override NodeState Evaluate()
        {
            Vector3 playerPosition = tree.GetMonsterData<GameObject>(MonsterData.v3SpawnPosition).transform.position;
            tree.SetBTData<Vector3>(BTData.v3PlayerPosition, playerPosition);

            float playerDistance = Vector3.SqrMagnitude(playerPosition - transform.position);
            tree.SetBTData<float>(BTData.fPlayerDistanceSqr, playerDistance);

            float spawnDistance = Vector3.SqrMagnitude(tree.GetMonsterData<Vector3>(MonsterData.v3SpawnPosition));
            tree.SetBTData<float>(BTData.fSpawnDistanceSqr, spawnDistance);

            if (spawnDistance > tree.GetMonsterData<MonsterStatData>(MonsterData.MonsterStat).overtravelDist)
                tree.SetBTData<bool>(BTData.bOvertraveld, true);

            return NodeState.SUCCESS;
        }
    }
}