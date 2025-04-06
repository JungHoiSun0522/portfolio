using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class soundstop : MonoBehaviour
{
    public AudioSource audioSource;

    // Start is called before the first frame update
    void Start()
    {
        Invoke("stop", 10f);

    }

    void stop()
    {
        audioSource.Stop();
    }

}