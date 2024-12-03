using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class help : MonoBehaviour
{
    public GameObject canvas;
    public GameObject main;
    bool state = false;
    public static int count;

    // Start is called before the first frame update
    void Start()
    {
        if (count != 1)
            main.SetActive(false);
        else
            canvas.SetActive(false);
    }

    // Update is called once per frame
    void Update()
    {
        if(state == true)
        {
            canvas.SetActive(false);
            main.SetActive(true);
            state = false;
        }
    }

    public void OnClickButton()
    {
        Debug.Log("Å¬¸¯");
        state = true;
    }
}
