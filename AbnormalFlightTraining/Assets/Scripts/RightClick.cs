using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class RightClick : MonoBehaviour
{
    public Transform Righthand;
    GameObject obj;

    // Update is called once per frame
    void Update()
    {
        Ray ray = new Ray(Righthand.position, Righthand.forward);
        RaycastHit hit;
        if (OVRInput.GetDown(OVRInput.Button.SecondaryHandTrigger))
        {
            if (Physics.Raycast(ray, out hit, 1000.0f))
            {
                Debug.DrawRay(Righthand.position, Righthand.forward * hit.distance, Color.blue);

                if (hit.transform != null)
                {
                    string start = "Start", option = "Option", quit = "Quit", ok = "Ok";

                    if (OVRInput.GetDown(OVRInput.Button.One))
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
