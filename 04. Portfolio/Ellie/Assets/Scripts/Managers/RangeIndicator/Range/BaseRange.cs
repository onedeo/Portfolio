using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class BaseRange : MonoBehaviour
{
    // �����ϴ� ���� ������Ʈ
    public GameObject RangeObject { get; private set; }
    public Transform Original { get; private set; }
    public Material DetectionMaterial { get; protected set; }
    public float FadeInTime { get; set; }
    public float FadeOutTime { get; set; }
    public float RemainTime { get; set; }
    public bool IsShowRange { get; set; }

    private const float RAYCAST_STARTPOS_OFFSET = 3.0f;
    private const float POSITION_OFFSET = 0.1f;

    private bool isFollowOrigin;
    private float initialYPosition;

    private void LateUpdate()
    {
        if (!isFollowOrigin)
            return;

        FollowOriginal();
    }

    private void FollowOriginal()
    {
        // Original�� position�� rotation�� �����ɴϴ�.
        Vector3 position = Original.position;
        Quaternion rotation = Original.rotation;

        // position�� y���� InitialYPosition���� �����մϴ�.
        position.y = initialYPosition;

        // RangeObject�� position�� rotation�� �����մϴ�.
        RangeObject.transform.position = position;
        RangeObject.transform.rotation = rotation;
    }

    public virtual void Init(GameObject rangeObject, RangePayload payload)
    {
        RangeObject = rangeObject;
        isFollowOrigin = payload.IsFollowOrigin;
        Original = payload.Original;
        IsShowRange = payload.IsShowRange;

        if (Original == null)
        {
            InitTransformByValue(rangeObject, payload);
        }
        else
        {
            InitTransformByOrigin(rangeObject, payload);
        }
    }

    private void InitTransformByOrigin(GameObject rangeObject, RangePayload payload)
    {
        // Ground ���̾ ������ �ִ� ������Ʈ�� �����ϴ� ���̾� ����ũ�� �����մϴ�.
        Vector3 position = Original.position;
        Quaternion rotation = Original.rotation;
        int groundLayer = LayerMask.GetMask("Ground");

        // -Vector3.up �������� Raycast�� �߻��մϴ�.
        RaycastHit hit;
        Vector3 checkPosition = position + new Vector3(0, RAYCAST_STARTPOS_OFFSET, 0);
        if (Physics.Raycast(checkPosition, -Vector3.up, out hit, Mathf.Infinity, groundLayer))
        {
            // Raycast�� Ground ���̾ ������ �ִ� ������Ʈ�� �¾Ҵٸ�, �� ��ġ�� ���� ������Ʈ�� �����մϴ�.
            initialYPosition = hit.point.y + POSITION_OFFSET;
            position = hit.point + new Vector3(0, POSITION_OFFSET, 0);
        }

        RangeObject.transform.position = position;
        RangeObject.transform.rotation = rotation;
    }

    private void InitTransformByValue(GameObject rangeObject, RangePayload payload)
    {
        // RangePayload���� StartPosition�� StartRotation ���� �����ɴϴ�.
        Vector3 position = payload.StartPosition;
        Quaternion rotation = payload.StartRotation;

        // Ground ���̾ ������ �ִ� ������Ʈ�� �����ϴ� ���̾� ����ũ�� �����մϴ�.
        int groundLayer = LayerMask.GetMask("Ground");

        // -Vector3.up �������� Raycast�� �߻��մϴ�.
        RaycastHit hit;
        Vector3 checkPosition = position + new Vector3(0, RAYCAST_STARTPOS_OFFSET, 0);
        if (Physics.Raycast(checkPosition, -Vector3.up, out hit, Mathf.Infinity, groundLayer))
        {
            // Raycast�� Ground ���̾ ������ �ִ� ������Ʈ�� �¾Ҵٸ�, �� ��ġ�� ���� ������Ʈ�� �����մϴ�.
            initialYPosition = hit.point.y + POSITION_OFFSET;
            position.y = initialYPosition;
        }

        // RangeObject�� ��ġ�� ȸ���� �����մϴ�.
        RangeObject.transform.position = position;
        RangeObject.transform.rotation = rotation;
    }

    public void StartFadeInAndOut(RangePayload payload)
    {
        FadeInTime = payload.FadeInTime;
        FadeOutTime = payload.FadeOutTime;
        RemainTime = payload.RemainTime;

        StartCoroutine(FadeInAndOutRoutine(FadeInTime, FadeOutTime, RemainTime));
    }

    public void FadeOutAndDestroy()
    {
        StopAllCoroutines();

        StartCoroutine(FadeOutDestroyRoutine(FadeOutTime));
    }

    private IEnumerator FadeInAndOutRoutine(float fadeInTime, float fadeOutTime, float remainTime)
    {
        // Fade in
        yield return StartCoroutine(FadeRoutine(0.0f, 0.5f, fadeInTime));

        if (remainTime > 0.0f)
        {
            // Remain
            yield return new WaitForSeconds(remainTime);

            // Fade out
            yield return StartCoroutine(FadeRoutine(0.5f, 0.0f, fadeOutTime));

            // Destroy the range object after fade out
            Destroy(RangeObject);
        }
    }

    private IEnumerator FadeOutDestroyRoutine(float fadeOutTime)
    {
        yield return StartCoroutine(FadeRoutine(0.5f, 0.0f, fadeOutTime));

        Destroy(RangeObject);
    }

    private IEnumerator FadeRoutine(float startAlpha, float endAlpha, float duration)
    {
        float elapsed = 0.0f;
        Color currentColor = DetectionMaterial.GetColor("_TintColor");

        while (elapsed < duration)
        {
            float alpha = Mathf.Lerp(startAlpha, endAlpha, elapsed / duration);
            currentColor.a = alpha;
            DetectionMaterial.SetColor("_TintColor", currentColor);
            elapsed += Time.deltaTime;
            yield return null;
        }

        currentColor.a = endAlpha;
        DetectionMaterial.SetColor("_TintColor", currentColor);
    }

    public abstract void CreateRange(RangePayload payload);
    public abstract List<Transform> CheckRange(string checkTag = null, int layerMask = -1);
}
