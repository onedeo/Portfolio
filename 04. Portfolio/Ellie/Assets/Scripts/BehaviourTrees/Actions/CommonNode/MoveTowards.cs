using UnityEngine;
using TheKiwiCoder;

[System.Serializable]
public class MoveTowards : ActionNode
{
    public NodeProperty<Vector3> targetPosition;
    public NodeProperty<Transform> targetTransform;
    public NodeProperty<float> moveSpeed;

    protected override void OnStart() {
    }

    protected override void OnStop() {
    }

    protected override State OnUpdate()
    {
        float stoppingDistanceSqr = 0.001f;

        // Vector3�� �̵�
        if (targetTransform.Value == null)
        {
            if ((context.transform.position - targetPosition.Value).sqrMagnitude < stoppingDistanceSqr)
            {
                return State.Success;
            }

            context.transform.position = Vector3.MoveTowards(context.transform.position, targetPosition.Value, moveSpeed.Value * Time.deltaTime);
        }
        // Transform���� �̵�
        else
        {
            if ((context.transform.position - targetTransform.Value.position).sqrMagnitude < stoppingDistanceSqr)
            {
                return State.Success;
            }

            context.transform.position = Vector3.MoveTowards(context.transform.position, targetTransform.Value.position, moveSpeed.Value * Time.deltaTime);
        }
        return State.Success;
    }
}
