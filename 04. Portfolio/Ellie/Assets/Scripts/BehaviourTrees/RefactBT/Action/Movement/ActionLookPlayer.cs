using UnityEngine;

namespace Scripts.BehaviourTrees.Monster
{
    public class ActionLookPlayer : MonsterNode
    {
        private float accumTime;
        private const float angle = 90.0f;
        private const float radius = 5.0f;

        public override NodeState Evaluate()
        {
            Vector3 playerPos = tree.GetBTData<Vector3>(BTData.v3PlayerPosition);
            Vector3 monsterPos = transform.position;
            Vector3 interV = playerPos - monsterPos;

            float dot = Vector3.Dot(interV.normalized, transform.forward.normalized);
            float theta = Mathf.Acos(dot);
            float degree = Mathf.Rad2Deg * theta;

            if (degree <= angle / 2.0f)
            {
                interV.y = 0;
                if (interV.sqrMagnitude <= radius * radius)
                    return NodeState.SUCCESS;
            }
            else
            {
                Quaternion targetRotation;
                Vector3 directionVector = interV;
                directionVector.y = 0;
                directionVector.Normalize();
                targetRotation = Quaternion.LookRotation(directionVector, Vector3.up);

                transform.rotation= Quaternion.Slerp(transform.rotation, targetRotation, Time.deltaTime * 90.0f);
                accumTime += Time.deltaTime;

                if (accumTime >= 0.5f) return NodeState.FAILURE;
            }

            return NodeState.RUNNING;
        }
    }
}
