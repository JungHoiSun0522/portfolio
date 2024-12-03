using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Click : MonoBehaviour
{
    public Transform LeftHand;
    public Transform RightHand;
    GameObject obj;
    GameObject slide;
    float delaySpeed = .0000005f;
    string handle = "Handle";
    string btn = "Button";

    // Start is called before the first frame update
    void Start()
    {
       
    }

    // Update is called once per frame
    void Update() // 
    {
        Ray LeftRay = new Ray(LeftHand.position, LeftHand.forward);
        Ray RightRay = new Ray(RightHand.position, RightHand.forward);
        RaycastHit hit;

        if (OVRInput.GetDown(OVRInput.Button.PrimaryHandTrigger)) // �޼� ��Ʈ�ѷ����� ������ ��� �κ��� Ʈ����
        {
            if (Physics.Raycast(LeftRay, out hit, 1000.0f))
            {
                //Debug.DrawRay(LeftHand.position, LeftHand.forward * hit.distance, Color.blue);
                //Gizmos.DrawLine(LeftHand.position, LeftHand.forward * hit.distance);
                if (hit.transform != null)
                {
                    if (OVRInput.GetDown(OVRInput.Button.Three))
                    {
                        if (hit.transform.gameObject.name == handle)
                        { 
                            StartCoroutine(handleLocate(hit.transform.position.x,
                            hit.transform.gameObject.GetComponent<RectTransform>().anchoredPosition.y));
                        }
                        else if (hit.transform.gameObject.name == btn)
                            hit.transform.gameObject.GetComponent<mainmenu>().OnClickBack();
                    }
                }
            }
        }
        else if(OVRInput.GetDown(OVRInput.Button.SecondaryHandTrigger))// ������ ��Ʈ�ѷ����� ������ ��� �κ��� Ʈ����
        {
            if (Physics.Raycast(RightRay, out hit, 1000.0f))
            {
                //Debug.DrawRay(RightHand.position, RightHand.forward * hit.distance, Color.blue);
                //Gizmos.DrawLine(p0, p1);

                if (hit.transform != null)
                {
                    if (OVRInput.GetDown(OVRInput.Button.One))
                    {
                        if (hit.transform.gameObject.name == handle)
                        {
                            StartCoroutine(handleLocate(hit.transform.position.x,
                            hit.transform.gameObject.GetComponent<RectTransform>().anchoredPosition.y));
                        }
                        else if (hit.transform.gameObject.name == btn)
                            hit.transform.gameObject.GetComponent<mainmenu>().OnClickBack();
                    }
                }
            }
        }
    }

    IEnumerator handleLocate(float x, float y) // �����̴� �ڵ� ��ġ ����
    {
        obj = GameObject.Find("Handle");
        float loc = 1000.0f; // ���Ƿ� ū ���� ����
        loc -= x;
        slide = GameObject.Find("SliderVol");

        if (loc < 1000.0f) // ������ ������ �����ų� ������ ��ŭ�� ���ϰ� �׸�ŭ �����̴��� �ڵ��� ������
        {
            loc = loc - 1000.0f;
            obj.GetComponent<RectTransform>().anchoredPosition = new Vector3(loc, y);
            slide.GetComponent<SoundManager>().ChangeVolume();
        }
        else if(loc > 1000.0f)
        {
            loc = 1000.0f - loc;
            obj.GetComponent<RectTransform>().anchoredPosition = new Vector3(loc, y);
            slide.GetComponent<SoundManager>().ChangeVolume();
        }

        yield return new WaitForSeconds(delaySpeed);
    }
}

