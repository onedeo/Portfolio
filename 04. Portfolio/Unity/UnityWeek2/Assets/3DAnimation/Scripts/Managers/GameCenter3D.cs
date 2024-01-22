using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameCenter3D : Singleton<GameCenter3D>
{
    public SpawnManager3D spawnerManager;
    private int iLevel = 0;
    private bool bGamePlaying;
    private PlayerControl3D player;
    private UI3D ui;
    private Camera minimapCamera;

    private void Start()
    {
        player = GameObject.Find("Player").GetComponent<PlayerControl3D>();
        spawnerManager = GameObject.Find("SpawnerManager").GetComponent<SpawnManager3D>();
        ui = GameObject.Find("UI3D").GetComponent<UI3D>();
        minimapCamera = GameObject.Find("MiniMapCamera").GetComponent<Camera>();
        minimapCamera.gameObject.SetActive(false);
    }
    public void GameStart()
    {
        DataManager3D.GetInstance().Restart();
        iLevel = 0;
        IncreaseLevel();
        bGamePlaying = true;
        player.ChangeGamePlaying();
        Cursor.lockState = CursorLockMode.Locked;
        Cursor.visible = false;
        minimapCamera.gameObject.SetActive(true);
    }
    public void IncreaseLevel()
    {
        spawnerManager.Spawn();
        iLevel++;
    }
    public void GameOver()
    {
        bGamePlaying = false;
        player.GameOver();
        spawnerManager.DestroyAllSpawners();
        ui.GameOver();
        Cursor.lockState = CursorLockMode.None;
        Cursor.visible = true;
        minimapCamera.gameObject.SetActive(false);
    }

    public int GetLevel()
    {
        return iLevel;
    }
    public bool GetGamePlaying()
    {
        return bGamePlaying;
    }
}
