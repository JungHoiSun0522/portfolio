using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class Sound : MonoBehaviour
{
    private AudioSource audioSource;
    private GameObject[] musics;
    private void Awake()
    {
        audioSource = GetComponent<AudioSource>();
    }
    public void PlayMusic()
    {
        if (audioSource.isPlaying) return;
        audioSource.Play();
    }

    public void StopMusic()
    {
        audioSource.Stop();
    }
}