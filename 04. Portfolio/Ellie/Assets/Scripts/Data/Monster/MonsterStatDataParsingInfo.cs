using System;
using System.Collections;
using System.Collections.Generic;
using Channels.Combat;
using UnityEngine;
using static Assets.Scripts.Monsters.Utility.Enums;

[Serializable]
public class MonsterStatData
{
    public string name;
    public float HP;
    public float speed;
    public float rotationSpeed;
    public float detectPlayerDist;
    public float detectChaseDist;
    public float overtravelDist;
    public float overtravelReturnSpeed;
    public float stopDistance;
    public float weeknessRatio;
    public float respawnTime;
    public List<int> itemTableNum;
    public Vector3 spawnPosition;
}


public class MonsterStatDataParsingInfo : DataParsingInfo
{
    public override T GetIndexData<T>(int index)
    {
        throw new NotImplementedException();
    }

    public override void Parse()
    {
        throw new NotImplementedException();
    }
}
