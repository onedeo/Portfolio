using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System;


//���� ������ �������� ��ȯ
[System.Serializable] public class SaveInformation
{
    public string name;
    public float PosX;
    public float PosY;
    public float PosZ;
}


public class SaveLoad : MonoBehaviour
{

    private void Update()
    {
        SaveLoad_Test();

    }

    private void SaveLoad_Test()
    {
        if (Input.GetKeyDown(KeyCode.A))
        {
            if (PlayerPrefs.HasKey("ID")) //���ڿ��� ��� ����Ǿ��ִ°� ã�°� (Dictionary ����)
            {
                string getID = PlayerPrefs.GetString("ID");
                //string.Format() : C�� pritnf�� �����ϸ� �ȴ�. {0},{1}�� ù ��°, �� ��° ���������� ���� (���� �������)
                Debug.Log(string.Format("ID : {0}", getID));
            }
            else
            {
                Debug.Log("ID ����");
            }
        }

        if (Input.GetKeyDown(KeyCode.B))
        {
            string setID = "baedon";
            PlayerPrefs.SetString("ID", setID);
            Debug.Log("Saved ID : " + setID);
        }

        if (Input.GetKeyDown(KeyCode.C))
        {
            PlayerPrefs.SetInt("Score", 33);
            PlayerPrefs.SetFloat("Exp", 44.4f);

            int getScore = 0;
            if (PlayerPrefs.HasKey("Score"))
            {
                getScore = PlayerPrefs.GetInt("Score");
            }
            float getExp = 0f;
            if (PlayerPrefs.HasKey("Exp"))
            {
                getExp = PlayerPrefs.GetFloat("Exp");
            }

            Debug.Log(string.Format("Score : {0} , Exp : {1}", getScore, getExp));
        }

        if(Input.GetKeyDown(KeyCode.D))
        {
            string getID = PlayerPrefs.GetString("ID2", "NONE"); //Key ���� ��������, ���� Key�� ���ٸ� NONE���� ��ȯ�Ѵٴ� �ǹ�
            Debug.Log(getID);
        }

        if (Input.GetKeyDown(KeyCode.S))
        {
            SaveBinary();
        }


    }

    private void SaveBinary()
    {
        // >> : ���� �Է�
        SaveInformation setInfo = new SaveInformation();
        setInfo.name = "Baedon";
        setInfo.PosX = 0.0f;
        setInfo.PosY = 4.5f;
        setInfo.PosZ = 5.5f;
        // << : ���� �Է�

        // >> : ����
        BinaryFormatter formatter = new BinaryFormatter();
        MemoryStream memStream = new MemoryStream();

        formatter.Serialize(memStream, setInfo);
        byte[] bytes = memStream.GetBuffer();
        String memStr = Convert.ToBase64String(bytes);
        

        PlayerPrefs.SetString("SaveInformation", memStr);
        // << : ����

        // >> : �ε�
        string getInfo = PlayerPrefs.GetString("SaveInformation");
        Debug.Log(getInfo);

        byte[] getBytes = Convert.FromBase64String(getInfo);

        MemoryStream getMemStream = new MemoryStream(getBytes);

        BinaryFormatter formatter2 = new BinaryFormatter();
        SaveInformation getInformation = (SaveInformation)formatter2.Deserialize(getMemStream);

        Debug.Log(getInformation.name);
        

        // << : �ε�


    }


}
