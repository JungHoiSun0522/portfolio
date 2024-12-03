using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class GameTextControl : MonoBehaviour
{
    public GameObject readText1;
    public GameObject readText;
    public static GameTextControl instance;


    void Awake()
    {
        if (GameTextControl.instance == null)
            GameTextControl.instance = this;
    }
    // Use this for initialization
    void Start()
    {
        StartCoroutine(ShowReady());
    }

    IEnumerator ShowReady()
    {
        yield return new WaitForSeconds(10.0f);
        readText.SetActive(true);
        readText1.SetActive(false);
    }

    // Update is called once per frame
    void Update()
    {
     
    }
}
