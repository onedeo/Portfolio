using UnityEngine;
using TheKiwiCoder;

[System.Serializable]
public class CheckCurrentAnimationTimeFailure : ActionNode
{
    public NodeProperty<int> layerIndex;
    public NodeProperty<float> checkTimeValue;

    private float tolerance = 0.03f;

    protected override void OnStart()
    {
    }

    protected override void OnStop()
    {
    }

    protected override State OnUpdate()
    {
        if (checkTimeValue.Value < 0.0f || checkTimeValue.Value > 1.0f)
        {
            Debug.Log("�ִϸ��̼� ���� üũ ���� �߸��Ǿ����ϴ�.");
            return State.Failure;
        }

        AnimatorStateInfo stateInfo = context.animator.GetCurrentAnimatorStateInfo(layerIndex.Value);

        float currentAnimationPer = stateInfo.normalizedTime % 1.0f;
        if (currentAnimationPer >= checkTimeValue.Value && currentAnimationPer <= checkTimeValue.Value + tolerance)
        {
            return State.Success;
        }

        return State.Failure;
    }
}
