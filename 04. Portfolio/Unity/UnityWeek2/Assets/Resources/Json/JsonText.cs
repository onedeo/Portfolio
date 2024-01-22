using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using LitJson;

/*
 * Json�� �����Ϳ��� �ν��� ���� �ʴ�.
 * �ε��� ���� �ɸ� ���� �ڷ�ƾ�� ����ϴ°�����. ������ ���纸�� �� �ִ�.
 *  ������� public���� �ؾ��Ѵ�. �Ǵ� serialize�� ����� �Ѵ�.
 *  
 *  
 */

public class PlayerInfo
{
    public int ID;
    public string Name;
    public double Gold;

    public PlayerInfo(int id, string name, double gold)
    {
        ID = id;
        Name = name;
        Gold = gold;
    }
}
public class JsonText : MonoBehaviour
{
    public List<PlayerInfo> playerinfoList = new List<PlayerInfo>();

    private void Start()
    {
        //SavePlayerInfo();
        LoadPlayerInfo();
    }

    public void SavePlayerInfo()
    {
        Debug.Log("SavePlayerInfo()");
        playerinfoList.Add(new PlayerInfo(1, "name1", 100));
        playerinfoList.Add(new PlayerInfo(2, "name2", 200));
        playerinfoList.Add(new PlayerInfo(3, "name3", 300));
        playerinfoList.Add(new PlayerInfo(4, "name4", 400));
        playerinfoList.Add(new PlayerInfo(5, "name5", 500));

        JsonData infoJson = JsonMapper.ToJson(playerinfoList);
        File.WriteAllText(Application.dataPath + "/Resources/Data/PlayerInfoData.json",infoJson.ToString());

    }

    public void LoadPlayerInfo()
    {
        Debug.Log("LoadPlayerInfo()");
        if(File.Exists(Application.dataPath+ "/Resources/Data/PlayerInfoData.json"))
        {
            string jsonString = File.ReadAllText(Application.dataPath + "/Resources/Data/PlayerInfoData.json");
            Debug.Log(jsonString);

            JsonData playerData = JsonMapper.ToObject(jsonString);
            ParsingJsonPlayerInfo(playerData);
        }
    }

    private void ParsingJsonPlayerInfo(JsonData data)
    {
        Debug.Log("ParsingJsonPlayerInfo()");
        
        for(int i=0; i<data.Count;i++)
        {
            print(data[i]["ID"] + " , " + data[i]["Name"] + " , " + data[i]["Gold"]);

            //����ȯ �ʼ�
            int id = (int)data[i]["ID"];
            print(id.ToString());
            double  gold = (double)data[i]["Gold"];
            print(gold.ToString());
        }
    }

}
