using UnityEngine;
using TheKiwiCoder;
using Assets.Scripts.Particle;

[System.Serializable]
public class EarthQuakeParticle : ActionNode
{
    public NodeProperty<GameObject> effectPrefab;
    public NodeProperty<Vector3> scale;

    public NodeProperty<float> forwardOffset;
    public NodeProperty<float> angle;
    public NodeProperty<int> particleCount;

    protected override void OnStart()
    {
        if (scale.Value == Vector3.zero)
            scale.Value = Vector3.one;
    }

    protected override void OnStop()
    {
    }

    protected override State OnUpdate()
    {
        if (effectPrefab == null)
            return State.Failure;

        // ���� ��ġ ��� (transform�� ���� ���⿡ forwardOffset��ŭ �̵�)
        Vector3 startPos = context.transform.position + (context.transform.forward * forwardOffset.Value);
        Quaternion startRotation = context.transform.rotation;

        // �� ��ƼŬ�� ���� ���� ���
        float totalAngle = angle.Value;
        float angleStep = totalAngle / (particleCount.Value - 1);

        for (int i = 0; i < particleCount.Value; i++)
        {
            // ���� ��ƼŬ�� ���� ���
            float currentAngle = -totalAngle / 2 + angleStep * i;
            Quaternion rotation = Quaternion.Euler(0, currentAngle, 0) * context.transform.rotation;

            // ��ƼŬ ���� (��� ��ƼŬ�� startPos���� ����)
            CreateParticle(startPos, rotation);
        }

        return State.Success;
    }

    private void CreateParticle(Vector3 position, Quaternion rotation)
    {
        ParticleManager.Instance.GetParticle(effectPrefab.Value, new ParticlePayload
        {
            Position = position,
            Rotation = rotation,
            Scale = scale.Value,
        });
    }
}
