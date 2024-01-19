using Assets.Scripts.Managers;
using System.Collections.Generic;
using UnityEngine;
using Assets.Scripts.Utils;
public enum RangeType
{
    None,
    Cone,       // ��ä��
    Circle,     // ��
    Trapezoid,  // ��ٸ���
    Rectangle,  // �簢��
    HybridCone, // ��ä�� + ��ٸ���
}

public class RangePayload : IBaseEventPayload
{
    // �⺻ ����
    public RangeType Type { get; set; }
    public Transform Original { get; set; }
    public Material DetectionMaterial { get; set; }
    public bool IsFollowOrigin { get; set; } = false;
    public bool IsShowRange { get; set; } = true;
    public Vector3 StartPosition { get; set; }
    public Quaternion StartRotation { get; set; }

    // ���ӽð�, ���̵� ��, ���̵� �ƿ�
    public float RemainTime { get; set; } = 0.0f; // 0.0f�̶�� ���� ����
    public float FadeInTime { get; set; } = 0.3f;
    public float FadeOutTime { get; set; } = 0.3f;

    // ��ä��, ��
    public float Radius { get; set; }
    public float Angle { get; set; }
    // �簢��(Width - ���� ����, Height - ��)
    public float Height { get; set; }
    public float Width { get; set; }
    // ��ä��(UpperBase - ����, LowerBase - ��) + Height
    public float UpperBase { get; set; }
    public float LowerBase { get; set; }
}

public class RangeManager : Singleton<RangeManager>
{
    [SerializeField] private Material baseMaterial;
    [SerializeField] private Material invisibleMaterial;

    public override void Awake()
    {
        base.Awake();

        baseMaterial = Resources.Load<Material>("Materials/Sensor");
        invisibleMaterial = Resources.Load<Material>("Materials/Sensor2");
    }

    public GameObject CreateRange(RangePayload payload)
    {
        if (payload == null)
            return null;

        if (payload.DetectionMaterial == null && baseMaterial != null)
            payload.DetectionMaterial = baseMaterial;

        GameObject obj = new GameObject();
        BaseRange range = null;

        switch (payload.Type)
        {
            case RangeType.Cone:
                range = obj.AddComponent<ConeRange>();
                break;
            case RangeType.Circle:
                range = obj.AddComponent<CircleRange>();
                break;
            case RangeType.Trapezoid:
                range = obj.AddComponent<TrapezoidRange>();
                break;
            case RangeType.Rectangle:
                range = obj.AddComponent<RectangleRange>();
                break;
            case RangeType.HybridCone:
                range = obj.AddComponent<HybridConeRange>();
                break;
        }

        if (range != null)
        {
            range.Init(obj, payload);
            range.CreateRange(payload);
            range.StartFadeInAndOut(payload);
            range.gameObject.GetOrAddComponent<VisibilityControl>();

            return obj;
        }

        return null;
    }


}