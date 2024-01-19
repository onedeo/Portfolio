using UnityEngine;
using TheKiwiCoder;

[System.Serializable]
public class MoveTowardsRunning : ActionNode
{
    public NodeProperty<Vector3> targetPosition;
    public NodeProperty<Transform> targetTransform;
    public NodeProperty<float> moveSpeed;
    public NodeProperty<float> moveDistance;

    private float travelledDistance;
    
    protected override void OnStart()
    {
        travelledDistance = 0.0f;
    }

    protected override void OnStop()
    {
    }
    protected override State OnUpdate()
    {
        float stoppingDistanceSqr = 0.001f; // 0.000001f
        float moveDistanceSqr = moveDistance.Value * moveDistance.Value; // �̵��ؾ� �� �Ÿ��� ����

        // Vector3 ���
        if (targetTransform.Value == null)
        {
            Vector3 currentPosition = context.transform.position;
            Vector3 directionToTarget = targetPosition.Value - currentPosition;
            if (directionToTarget.sqrMagnitude < stoppingDistanceSqr)
            {
                return State.Success;
            }

            Vector3 nextPosition = Vector3.MoveTowards(currentPosition, targetPosition.Value, moveSpeed.Value * Time.deltaTime);
            travelledDistance += (nextPosition - currentPosition).magnitude;

            if (travelledDistance * travelledDistance >= moveDistanceSqr) // ���������� ��
            {
                return State.Success;
            }

            context.transform.position = nextPosition;
        }
        // Transform ���
        else
        {
            Vector3 currentPosition = context.transform.position;
            Vector3 directionToTarget = targetTransform.Value.position - currentPosition;
            if (directionToTarget.sqrMagnitude < stoppingDistanceSqr)
            {
                return State.Success;
            }

            Vector3 nextPosition = Vector3.MoveTowards(currentPosition, targetTransform.Value.position, moveSpeed.Value * Time.deltaTime);
            travelledDistance += (nextPosition - currentPosition).magnitude;

            if (travelledDistance * travelledDistance >= moveDistanceSqr) // ���������� ��
            {
                return State.Success;
            }

            context.transform.position = nextPosition;
        }

        // ��ǥ�� �������� �ʾ����� Running ���� ����
        return State.Running;
    }

}
