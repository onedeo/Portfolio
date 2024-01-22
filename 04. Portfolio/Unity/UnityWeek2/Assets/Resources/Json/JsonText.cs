using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using LitJson;

/*
 * Json은 에디터에서 인식이 조금 늦다.
 * 로딩이 오래 걸릴 때는 코루틴을 사용하는게좋다. 게임이 멈춰보일 수 있다.
 *  저장용은 public으로 해야한다. 또는 serialize를 해줘야 한다.
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

            //형변환 필수
            int id = (int)data[i]["ID"];
            print(id.ToString());
            double  gold = (double)data[i]["Gold"];
            print(gold.ToString());
        }
    }

}
