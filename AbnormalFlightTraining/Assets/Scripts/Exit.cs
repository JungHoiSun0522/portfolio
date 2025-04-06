using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Exit : MonoBehaviour
{
    private GameObject obj;
    float ShakeTime2 = 0;
    private GameObject[] passenger = new GameObject[16];
    private bool state = true;
    protected Vector3 pos;
    float delaySpeed = 0.0005f;
    private Rigidbody rd;
    int count = 0;
    float distance = 0.38f; // �� ���� �� ����� ���� 0.303f

    // Start is called before the first frame update
    void Start()
    {
        obj = GameObject.Find("OVRPlayerController");
        int count1 = 1, count2 = 1;
        string str;

        for (int i = 0; i < 16; i++) //���� ����� ���� ���� ���� ������ �迭�� ����
        {
            if (i < 14)
            {
                if (i == 0 || (i % 2 == 0)) //i�� ¦���� �� ���� ������ �ټ���
                {
                    str = "G" + count1;
                    passenger[i] = GameObject.Find(str);
                    count1 += 1;
                }
                else if (i != 0 && (i % 2 != 0)) //i�� Ȧ���� �� ���� ������ �ټ���
                {
                    str = "M" + count2;
                    passenger[i] = GameObject.Find(str);
                    count2 += 1;
                }
            }
            else
            {
                str = "M" + count2;
                passenger[i] = GameObject.Find(str);
                count2 += 1;
            }
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (state == true)
        {
            ShakeTime2 = obj.GetComponent<CameraShake>().ShakeTime; // ī�޶� ��鸲�� ���� �� ���� ����� ����
                                                                    // CameraShake ��ũ��Ʈ���� �ش� ���� ���� ������
            if (ShakeTime2 < 0)
            {
                StartCoroutine(Line());
                state = false;
            }
        }
    }

    void OnTriggerExit(Collider other)
    {
        if (other.gameObject.name == passenger[count].gameObject.name)
        {
            GameObject.Find(other.gameObject.name).GetComponent<run>().enabled = true;
            GameObject.Find(other.gameObject.name).GetComponent<run>().ready = true;
            
            //StartCoroutine(Run(ob[count]));
            count += 1;
            StartCoroutine(StopWalk(count));
            for (int i = count; i < 16; i++)
            {
                //ob[i].GetComponent<Animator>().SetBool("walk", true) ���� true �ΰ� false��
                passenger[i].GetComponent<Animator>().SetBool("walk", false);
            }
        }
    }

    IEnumerator StopWalk(int count)
    {
        for (int i = count; i < 16; i++)
        {
            //ob[i].GetComponent<Animator>().SetBool("walk", true) ���� flase �ΰ� true��
            passenger[i].GetComponent<Animator>().SetBool("walk", true);
            passenger[i].transform.position += new Vector3(0, 0, distance);
            yield return new WaitForSeconds(0.1f);
        }
    }

    IEnumerator Line() // �� �����
    {
        pos = new Vector3(-1.421f, 5.20753002f, 19.2000008f);
        for (int i = 0; i < 16; i++)
        {          
            passenger[i].transform.position = pos;
            ConstraintsDisable(passenger[i]);
            passenger[i].GetComponent<Animator>().SetBool("down", true); //down ���� true�� standing���� ��ȯ
            pos -= new Vector3(0, 0, distance); // ����� ���ݸ�ŭ ������ z�� ����
            yield return new WaitForSeconds(delaySpeed);
        }
    }

    void ConstraintsDisable(GameObject ob) // ������ٵ� �������� ����
    {
        rd = ob.GetComponent<Rigidbody>();
        rd.constraints = RigidbodyConstraints.None; // �������� ���� ���� �� rotation z��� y��, x���� �ٽ� ���� ����
        rd.constraints = RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY | RigidbodyConstraints.FreezeRotationZ;
    }

    /*IEnumerator Run(GameObject ob)
   {
       ob.transform.Rotate(new Vector3(0, -80.0f, 0));
       //ob.GetComponent<Animator>().applyRootMotion = true;
       ob.GetComponent<Animator>().SetTrigger("run");
       //  ob.GetComponent<Animator>().SetBool("walk", false); �߰�
       ob.GetComponent<Animator>().SetBool("walk", false);
       yield return new WaitForSeconds(3f);
       //ob.transform.Rotate(new Vector3(0, -80.0f, 0));
   }*/
}