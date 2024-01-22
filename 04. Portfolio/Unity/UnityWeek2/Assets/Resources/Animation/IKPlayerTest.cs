using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IKPlayerTest : MonoBehaviour
{
    private GameObject unichan;
    enum Parts { RightHand, LeftHand, RightFoot, LeftFoot, Head, End}
    private Transform[] bodyParts;
    private float   defaultSpeed = 0.0005f;
    private float rotationSpeed = 10f;

    float[] moveSpeed;
    private bool bCliming;
    private float fHeadPos = 0.2f;

    private float fHandUpPos = 0.72f;
    private float fHandDownPos = 0.62f;

    private float fFootUpPos = 0.26f;
    private float fFootDownPos = 0.1f;
        
    [Range(0, 1)] public float posWeight = 1;
    [Range(0, 1)] public float rotWeight = 0;
    protected Animator animator;
    private int selectWeight = 1;
    [Range(0, 359)] public float xRotation = 0.0f;
    [Range(0, 359)] public float yRotation = 0.0f;
    [Range(0, 359)] public float zRotation = 0.0f;

    private void Start()
    {
        unichan = GameObject.Find("unitychan");

        animator = GetComponent<Animator>();
        bodyParts = new Transform[(int)Parts.End];
        bodyParts[(int)Parts.RightHand] = transform.Find("RightHand");
        bodyParts[(int)Parts.LeftHand] = transform.Find("LeftHand");
        bodyParts[(int)Parts.RightFoot] = transform.Find("RightFoot");
        bodyParts[(int)Parts.LeftFoot] = transform.Find("LeftFoot");
        bodyParts[(int)Parts.Head] = transform.Find("Head");

        moveSpeed = new float[(int)Parts.End];
        moveSpeed[(int)Parts.RightHand] = defaultSpeed;
        moveSpeed[(int)Parts.LeftHand] = defaultSpeed;
        moveSpeed[(int)Parts.RightFoot] = defaultSpeed * 1.6f;
        moveSpeed[(int)Parts.LeftFoot] = defaultSpeed * 1.6f;
        moveSpeed[(int)Parts.Head] = defaultSpeed * 4f;
    }

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
            if (!bCliming) StartCliming();
        if(Input.GetKey(KeyCode.W))
        {
            ClimeWall(true);
        }
        if(Input.GetKey(KeyCode.S))
        {
            ClimeWall(false);
        }

    }

        Vector3[] newPos = new Vector3[(int)Parts.End];
        int iAdd = 1;
        float fAccum = 0;
    private void StartCliming()
    {
        bCliming = true;
        bodyParts[(int)Parts.Head].localPosition = new Vector3(fHeadPos, 1f, 0.1f);
        bodyParts[(int)Parts.RightHand].localPosition = new Vector3(bodyParts[(int)Parts.RightHand].position.x, fHandUpPos, 0.03f);
        bodyParts[(int)Parts.LeftHand].localPosition = new Vector3(bodyParts[(int)Parts.LeftHand].position.x, fHandDownPos, 0.03f);
        bodyParts[(int)Parts.RightFoot].localPosition = new Vector3(bodyParts[(int)Parts.RightFoot].position.x, fFootUpPos, 0.2f);
        bodyParts[(int)Parts.LeftFoot].localPosition = new Vector3(bodyParts[(int)Parts.LeftFoot].position.x, fFootDownPos, 0.2f);

        unichan.transform.Rotate(Vector3.right * 19f);
    }
    private void ClimeWall(bool up)
    {
        int goUp;
        goUp = up == true ? 1 : -1;
        if (!bCliming)
        {
            StartCliming();
        }

        bodyParts[(int)Parts.Head].Translate(Vector3.right * moveSpeed[(int)Parts.Head] * -iAdd);
        bodyParts[(int)Parts.RightHand].Translate(Vector3.up * moveSpeed[(int)Parts.RightHand] * -iAdd);
        bodyParts[(int)Parts.LeftHand].Translate(Vector3.up * moveSpeed[(int)Parts.RightHand] * iAdd);
        bodyParts[(int)Parts.RightFoot].Translate(Vector3.up * moveSpeed[(int)Parts.RightFoot] * -iAdd);
        bodyParts[(int)Parts.LeftFoot].Translate(Vector3.up * moveSpeed[(int)Parts.LeftFoot] * iAdd);


        transform.Translate(Vector3.up * defaultSpeed * goUp);

        fAccum += defaultSpeed;
        if (fAccum > 0.1)
        {
            iAdd *= -1;
            fAccum = 0;
        }
    }

    private void SetPositionRotation()
    {
        animator.SetIKPositionWeight(AvatarIKGoal.RightHand, posWeight);
        animator.SetIKPositionWeight(AvatarIKGoal.LeftHand, posWeight);
        animator.SetIKPositionWeight(AvatarIKGoal.RightFoot, posWeight);
        animator.SetIKPositionWeight(AvatarIKGoal.LeftFoot, posWeight);
        
        animator.SetIKRotationWeight(AvatarIKGoal.RightHand, rotWeight);
        animator.SetIKRotationWeight(AvatarIKGoal.LeftHand, rotWeight);
        animator.SetIKRotationWeight(AvatarIKGoal.RightFoot, rotWeight);
        animator.SetIKRotationWeight(AvatarIKGoal.LeftFoot, rotWeight);

        animator.SetIKPosition(AvatarIKGoal.RightHand, bodyParts[(int)Parts.RightHand].position);
        animator.SetIKPosition(AvatarIKGoal.LeftHand, bodyParts[(int)Parts.LeftHand].position);
        animator.SetIKPosition(AvatarIKGoal.RightFoot, bodyParts[(int)Parts.RightFoot].position);
        animator.SetIKPosition(AvatarIKGoal.LeftFoot, bodyParts[(int)Parts.LeftFoot].position);

        animator.SetLookAtWeight(1);
        animator.SetLookAtPosition(bodyParts[(int)Parts.Head].position);
    }

    private void OnAnimatorIK(int layerIndex)
    {
        SetPositionRotation();

    }
    /*
    private void SetPositionWeight()
    {
        animator.SetIKPositionWeight(AvatarIKGoal.RightHand, posWeight);
        animator.SetIKRotationWeight(AvatarIKGoal.RightHand, 0f);

        animator.SetIKPosition(AvatarIKGoal.RightHand, rightHandFollowObj.position);
        Quaternion handRotation = Quaternion.LookRotation(rightHandFollowObj.position - transform.position);
        animator.SetIKRotation(AvatarIKGoal.RightHand, handRotation);
    }
    private void SetRotationWeight()
    {
        animator.SetIKPositionWeight(AvatarIKGoal.RightHand, 0.0f);
        animator.SetIKRotationWeight(AvatarIKGoal.RightHand, rotWeight);

        animator.SetIKPosition(AvatarIKGoal.RightHand, rightHandFollowObj.position);
        Quaternion handRotation = Quaternion.LookRotation(rightHandFollowObj.position - transform.position);
        animator.SetIKRotation(AvatarIKGoal.RightHand, handRotation);
    }
    private void SetEachWeight()
    {
        animator.SetIKPositionWeight(AvatarIKGoal.RightHand, posWeight);
        animator.SetIKRotationWeight(AvatarIKGoal.RightHand, rotWeight);

        animator.SetIKPosition(AvatarIKGoal.RightHand, rightHandFollowObj.position);
        Quaternion handRotation = Quaternion.LookRotation(rightHandFollowObj.position - transform.position);
        animator.SetIKRotation(AvatarIKGoal.RightHand, handRotation);
    }
    private void SetRotationAngle()
    {
        animator.SetIKPositionWeight(AvatarIKGoal.RightHand, posWeight);
        animator.SetIKRotationWeight(AvatarIKGoal.RightHand, rotWeight);

        animator.SetIKPosition(AvatarIKGoal.RightHand, rightHandFollowObj.position);

        Quaternion handRotation = Quaternion.Euler(xRotation, yRotation, zRotation);
        animator.SetIKRotation(AvatarIKGoal.RightHand, handRotation);
    }
    private void SetLookAtObj()
    {
        animator.SetLookAtWeight(1);
        animator.SetLookAtPosition(rightHandFollowObj.position);
    }
    private void SetLegWeight()
    {
        animator.SetIKPositionWeight(AvatarIKGoal.RightFoot, posWeight);
        animator.SetIKRotationWeight(AvatarIKGoal.RightFoot, rotWeight);

        animator.SetIKPosition(AvatarIKGoal.RightFoot, rightHandFollowObj.position);

        Quaternion handRotation = Quaternion.Euler(xRotation, yRotation, zRotation);
        animator.SetIKRotation(AvatarIKGoal.RightFoot, handRotation);
    }
    */
}
