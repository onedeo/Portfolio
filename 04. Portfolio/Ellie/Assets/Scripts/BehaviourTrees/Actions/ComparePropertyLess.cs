using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TheKiwiCoder;

[System.Serializable]
public class ComparePropertyLess : ActionNode
{
    public NodeProperty nodeValue;
    public NodeProperty<float> compareValue;
    public NodeProperty<bool> isEqual;

    private float val;
    private float compare;

    protected override void OnStart()
    {
        compare = compareValue.Value;
    }

    protected override void OnStop()
    {
    }

    protected override State OnUpdate()
    {
        BlackboardKey<float> valFloat = nodeValue.reference as BlackboardKey<float>;

        if (valFloat != null)
        {
            val = valFloat.Value;
        }
        else
        {
            // BlackboardKey<float> ����ȯ�� ���� �� int�� ���
            BlackboardKey<int> valInt = nodeValue.reference as BlackboardKey<int>;
            if (valInt != null)
            {
                // ���������� ����ȯ �� ���, float�� ĳ�����Ͽ� ���� ����մϴ�.
                val = (float)valInt.Value;
            }
            else
            {
                // �� �� ����ȯ�� ������ ���, Failure�� ��ȯ
                return State.Failure;
            }
        }

        if ((isEqual.Value == true && val <= compare) ||
           (isEqual.Value == false && val < compare))
        {
            return State.Success;
        }

        return State.Failure;
    }
}
