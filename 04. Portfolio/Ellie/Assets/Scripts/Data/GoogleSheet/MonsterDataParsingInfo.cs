using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum Element
{
    Darkness,
    Confuse,
    Normal,
    Earth,
    Fire,
    Water,
    Grass,
    Light,
}

[Serializable]
public class MonsterData
{
    public int index;
    public string name;
    public Element element;
    public int hp;
    public float movement;
    public float range;
    public float attackInterval;
    public List<Element> immuneList;
    public bool aggression;
    public float weakRatio;
    public int dropTable;
}

[CreateAssetMenu(fileName = "MonsterData", menuName = "GameData List/MonsterData")]
public class MonsterDataParsingInfo : DataParsingInfo
{
    public List<MonsterData> monsters;

    public override T GetIndexData<T>(int index) where T : class
    {
        if (typeof(T) == typeof(MonsterData))
        {
            return monsters.Find(m => m.index == index) as T;
        }
        return default(T);
    }

    public override void Parse()
    {
        monsters.Clear();

        string[] lines = tsv.Split('\n');

        for (int i = 0; i < lines.Length; i++)
        {
            if (string.IsNullOrEmpty(lines[i]))
                continue;

            string[] entries = lines[i].Split('\t');

            MonsterData data = new MonsterData();
            data.immuneList = new List<Element>();

            try
            {
                // �ε��� �ڵ�
                data.index = int.Parse(entries[0].Trim());

                // ���� �̸�(Kor)
                data.name = entries[1].Trim();

                // �Ӽ�
                data.element = (Element)Enum.Parse(typeof(Element), entries[2].Trim());

                // ü��
                data.hp = int.Parse(entries[3].Trim());

                // �̵� �ӵ�
                data.movement = float.Parse(entries[4].Trim());

                // ���� ����
                data.range = float.Parse(entries[5].Trim());

                // ���� ����(�ӵ�)
                data.attackInterval = float.Parse(entries[6].Trim());

                // �����̻� �鿪 - ����Ʈ
                string[] immuneElements = entries[7].Split(',');
                foreach (var element in immuneElements)
                {
                    if (element.Trim() == "None") continue;
                    data.immuneList.Add((Element)Enum.Parse(typeof(Element), element.Trim()));
                }

                // ���� ����
                data.aggression = bool.Parse(entries[8].Trim());

                // ���� ���
                data.weakRatio = float.Parse(entries[9].Trim());

                // ��� ���̺� ID
                data.dropTable = int.Parse(entries[10].Trim());
            }
            catch (Exception ex)
            {
                Debug.LogError($"Error parsing line {i + 1}: {entries[i]}");
                Debug.LogError(ex);
                continue;
            }

            monsters.Add(data);
        }
    }
}
