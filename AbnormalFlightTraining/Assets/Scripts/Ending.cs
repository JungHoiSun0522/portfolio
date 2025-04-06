using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Ending : MonoBehaviour
{
    public GameObject _canvas;
    GameObject obj;
    GameObject M9;
    public bool state;

    // Start is called before the first frame update
    void Start()
    {
        obj = GameObject.Find("UIcanvas");
        M9 = GameObject.Find("M9");
    }

    // Update is called once per frame
    void Update()
    {
        if (state == false)
        {
            if (M9.activeSelf == false)
            {
                Debug.Log("dd");
                state = true;
                StartCoroutine(ending());
            }
        }
    }

    IEnumerator ending()
    {
        yield return new WaitForSeconds(2.5f);
        obj.GetComponent<GameTextControl>().readText.SetActive(false);
        _canvas.SetActive(true);
        GameObject.Find("LaserPointer").GetComponent<LineRenderer>().enabled = true;
    }

    public void OnClickReturn()
    {
        SceneManager.LoadScene(0);
    }

    public void OnClickEnd()
    {
#if UNITY_EDITOR
UnityEditor.EditorApplication.isPlaying = false;
#else
        Application.Quit();
#endif
    }
}
