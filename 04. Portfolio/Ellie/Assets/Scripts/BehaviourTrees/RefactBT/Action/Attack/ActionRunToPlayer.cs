using UnityEngine;
using UnityEngine.AI;

namespace Scripts.BehaviourTrees.Monster
{
    public class ActionRunToPlayer : MonsterNode
    {
        private RunToPlayerData skill;
        private NavMeshAgent agent;
        private float originalSpeed;
        private float accumTime;

        public ActionRunToPlayer()
        {
            skill = tree.GetMonsterData<RunToPlayerData>(MonsterData.RunToPlayer);
            if (agent == null)
                agent = tree.GetComponentData<NavMeshAgent>(MonsterComponentData.AGENT);
            if (agent == null)
                DebugNull(transform, MonsterComponentData.AGENT);

            originalSpeed = tree.GetMonsterData<MonsterStatData>(MonsterData.MonsterStat).speed;
            accumTime = 0.0f;
        }
        protected override void OnStart()
        {
            agent.speed = skill.speed;
            isStarted = true;
        }
        public override NodeState Evaluate()
        {
            if (!isStarted)
                OnStart();

            Vector3 playerPos = tree.GetBTData<Vector3>(BTData.v3PlayerPosition);
            agent.destination = playerPos;
            float distance = Vector3.SqrMagnitude(playerPos - transform.position);

            if(accumTime<skill.duration)
            {
                if (distance < skill.stopDistance)
                {
                    OnExit();
                    return NodeState.SUCCESS;
                }
                accumTime += Time.deltaTime;
                return NodeState.RUNNING;
            }

            OnExit();
            return NodeState.SUCCESS;
        }

        protected override void OnExit()
        {
            agent.speed = originalSpeed;
            accumTime = 0.0f;
            isStarted = false;
        }
    }
}
