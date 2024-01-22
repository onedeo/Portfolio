using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundTest : MonoBehaviour
{
    public AudioClip[] audioClips = null;
    private AudioSource audioSource = null;
    private void Start()
    {
        audioSource = GetComponent<AudioSource>();


    }
    private void Update()
    {
        SoundTest1();
    }

    private void StopAndPlay(AudioClip clip)
    {
        audioSource.Stop();

        audioSource.clip = clip;
        audioSource.Play();
    }
    
    private void SoundTest1()
    {
        if (Input.GetKeyDown(KeyCode.Alpha1))
            StopAndPlay(audioClips[0]);
        if (Input.GetKeyDown(KeyCode.Alpha2))
            StopAndPlay(audioClips[1]);
        if (Input.GetKeyDown(KeyCode.Alpha3))
            StopAndPlay(audioClips[2]);
    }

}
