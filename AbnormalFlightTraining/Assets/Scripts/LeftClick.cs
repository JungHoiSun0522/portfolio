using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class LeftClick : MonoBehaviour
{
    public Transform Lefthand;
    GameObject obj;

    void Start()
    {
        obj = GameObject.Find("MainMeunCanvas");
    }

    // Update is called once per frame
    void Update()
    {
        Ray ray = new Ray(Lefthand.position, Lefthand.forward);
        RaycastHit hit;
        if (OVRInput.GetDown(OVRInput.Button.PrimaryHandTrigger))
        {
            if (Physics.Raycast(ray, out hit, 1000.0f))
            {
                Debug.DrawRay(Lefthand.position, Lefthand.forward * hit.distance, Color.blue);

                if (hit.transform != null)
                {
                    string start = "Start", option = "Option", quit = "Quit", ok = "Ok";

                    if (OVRInput.GetDown(OVRInput.Button.Three))
                    {
                        if (hit.transform.gameObject.name == start)
                            obj.GetComponent<mainmenu>().OnClickStart();
                  
                        else if (hit.transform.gameObject.name == option)
                            obj.GetComponent<mainmenu>().OnClickOption();
                   
                        else if (hit.transform.gameObject.name == quit)
                            obj.GetComponent<mainmenu>().OnClickQuit();

                        else if (hit.transform.gameObject.name == ok)
                            obj.GetComponent<help>().OnClickButton();
                    }
                }
            }
        }
    }
}
