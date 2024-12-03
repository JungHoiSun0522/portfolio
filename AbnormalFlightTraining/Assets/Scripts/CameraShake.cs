using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraShake : MonoBehaviour
{
    public AudioSource audioSource;
    public float ShakeAmount;
    public float ShakeTime = 16f; //��鸲�� ���ӽð� �� ��� ��ó �ð�
    Vector3 initialPosition;
    private GameObject ob;
    private Rigidbody rd;

    // Start is called before the first frame update
    void Start()
    {
        //��Ʈ�ѷ��� �������� Vector3 ������ �־���
        ob = GameObject.Find("OVRPlayerController");
        initialPosition = new Vector3(ob.transform.localPosition.x, ob.transform.localPosition.y,
            ob.transform.localPosition.z);
    }

    // Update is called once per frame
    void Update()
    {
        if (ShakeTime > 6f)
        {
            ob.transform.position = Random.insideUnitSphere * ShakeAmount + initialPosition;
            ShakeTime -= Time.deltaTime;
        }
        else if (ShakeTime == 6f)
        {
            ob.transform.position = initialPosition;
            rd = ob.GetComponent<Rigidbody>();
            rd.constraints = RigidbodyConstraints.None;
            ShakeTime -= Time.deltaTime;
        }
        else if (0 <= ShakeTime && ShakeTime < 6f)
        {
            if (ShakeTime > 0)
                ShakeTime -= Time.deltaTime;
            else if (ShakeTime == 0)
            {
                ShakeTime = -1f;
            }
        }
    }
}
