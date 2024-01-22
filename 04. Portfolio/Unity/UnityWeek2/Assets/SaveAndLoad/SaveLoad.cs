using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System;


//저장 가능한 형식으로 변환
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
            if (PlayerPrefs.HasKey("ID")) //문자열이 어디에 저장되어있는가 찾는거 (Dictionary 개념)
            {
                string getID = PlayerPrefs.GetString("ID");
                //string.Format() : C의 pritnf로 생각하면 된다. {0},{1}로 첫 번째, 두 번째 순차적으로 들어간다 (형식 상관없음)
                Debug.Log(string.Format("ID : {0}", getID));
            }
            else
            {
                Debug.Log("ID 없음");
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
            string getID = PlayerPrefs.GetString("ID2", "NONE"); //Key 값을 가져오고, 만약 Key가 없다면 NONE으로 반환한다는 의미
            Debug.Log(getID);
        }

        if (Input.GetKeyDown(KeyCode.S))
        {
            SaveBinary();
        }


    }

    private void SaveBinary()
    {
        // >> : 정보 입력
        SaveInformation setInfo = new SaveInformation();
        setInfo.name = "Baedon";
        setInfo.PosX = 0.0f;
        setInfo.PosY = 4.5f;
        setInfo.PosZ = 5.5f;
        // << : 정보 입력

        // >> : 저장
        BinaryFormatter formatter = new BinaryFormatter();
        MemoryStream memStream = new MemoryStream();

        formatter.Serialize(memStream, setInfo);
        byte[] bytes = memStream.GetBuffer();
        String memStr = Convert.ToBase64String(bytes);
        

        PlayerPrefs.SetString("SaveInformation", memStr);
        // << : 저장

        // >> : 로드
        string getInfo = PlayerPrefs.GetString("SaveInformation");
        Debug.Log(getInfo);

        byte[] getBytes = Convert.FromBase64String(getInfo);

        MemoryStream getMemStream = new MemoryStream(getBytes);

        BinaryFormatter formatter2 = new BinaryFormatter();
        SaveInformation getInformation = (SaveInformation)formatter2.Deserialize(getMemStream);

        Debug.Log(getInformation.name);
        

        // << : 로드


    }


}
