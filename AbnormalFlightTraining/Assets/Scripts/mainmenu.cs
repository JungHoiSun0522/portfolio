using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class mainmenu : MonoBehaviour
{
    public AudioSource audioSource;
    //Scene scene;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
    public void OnClickBack()
    {
        help.count = 1;
        SceneManager.LoadScene(0);
    }

    public void OnClickStart()
    {
        audioSource.Stop();
        SceneManager.LoadScene(2);
    }

    public void OnClickOption()
    {
        audioSource.Stop();
        SceneManager.LoadScene(1);
    }

    public void OnClickQuit()
    {
#if UNITY_EDITOR
UnityEditor.EditorApplication.isPlaying = false;
#else
        Application.Quit();
#endif
    }
}
