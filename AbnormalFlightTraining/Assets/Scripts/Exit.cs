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
    float distance = 0.38f; // 줄 세울 때 사람들 간격 0.303f

    // Start is called before the first frame update
    void Start()
    {
        obj = GameObject.Find("OVRPlayerController");
        int count1 = 1, count2 = 1;
        string str;

        for (int i = 0; i < 16; i++) //줄을 세우기 위해 남자 여자 교차로 배열에 넣음
        {
            if (i < 14)
            {
                if (i == 0 || (i % 2 == 0)) //i가 짝수일 때 여성 에셋을 줄세움
                {
                    str = "G" + count1;
                    passenger[i] = GameObject.Find(str);
                    count1 += 1;
                }
                else if (i != 0 && (i % 2 != 0)) //i가 홀수일 때 남성 에셋을 줄세움
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
            ShakeTime2 = obj.GetComponent<CameraShake>().ShakeTime; // 카메라 흔들림이 끝난 후 줄을 세우기 위해
                                                                    // CameraShake 스크립트에서 해당 변수 값을 가져옴
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
                //ob[i].GetComponent<Animator>().SetBool("walk", true) 원래 true 인거 false로
                passenger[i].GetComponent<Animator>().SetBool("walk", false);
            }
        }
    }

    IEnumerator StopWalk(int count)
    {
        for (int i = count; i < 16; i++)
        {
            //ob[i].GetComponent<Animator>().SetBool("walk", true) 원래 flase 인거 true로
            passenger[i].GetComponent<Animator>().SetBool("walk", true);
            passenger[i].transform.position += new Vector3(0, 0, distance);
            yield return new WaitForSeconds(0.1f);
        }
    }

    IEnumerator Line() // 줄 세우기
    {
        pos = new Vector3(-1.421f, 5.20753002f, 19.2000008f);
        for (int i = 0; i < 16; i++)
        {          
            passenger[i].transform.position = pos;
            ConstraintsDisable(passenger[i]);
            passenger[i].GetComponent<Animator>().SetBool("down", true); //down 값이 true면 standing으로 전환
            pos -= new Vector3(0, 0, distance); // 사람들 간격만큼 포지션 z값 조정
            yield return new WaitForSeconds(delaySpeed);
        }
    }

    void ConstraintsDisable(GameObject ob) // 리지드바디 제약조건 해제
    {
        rd = ob.GetComponent<Rigidbody>();
        rd.constraints = RigidbodyConstraints.None; // 제약조건 전부 해제 후 rotation z축과 y축, x축을 다시 제약 설정
        rd.constraints = RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY | RigidbodyConstraints.FreezeRotationZ;
    }

    /*IEnumerator Run(GameObject ob)
   {
       ob.transform.Rotate(new Vector3(0, -80.0f, 0));
       //ob.GetComponent<Animator>().applyRootMotion = true;
       ob.GetComponent<Animator>().SetTrigger("run");
       //  ob.GetComponent<Animator>().SetBool("walk", false); 추가
       ob.GetComponent<Animator>().SetBool("walk", false);
       yield return new WaitForSeconds(3f);
       //ob.transform.Rotate(new Vector3(0, -80.0f, 0));
   }*/
}