using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Item : MonoBehaviour
{
    private GameObject[] mesh;
    private float meshRotateSpeed = 360;

    private void Start()
    {
        mesh = new GameObject[4];
        string meshName;
        for (int i = 0; i < 4; i++)
        {
            meshName = "Mesh" + i;
            mesh[i] = transform.Find(meshName).gameObject;
        }

    }
    private void FixedUpdate()
    {
        for(int i=0; i<4;i++)
        {
            mesh[i].transform.Rotate(new Vector3(0, meshRotateSpeed * Time.deltaTime, 0));
        }

    }
}
