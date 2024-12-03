using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class opendoor : MonoBehaviour
{
    public float rotateSpeed = 10;
    float rotationAmount = 1f;
    float delaySpeed = .0000005f;
    float count = 0;

    float rotationAmount2 = 1f;
    float delaySpeed2 = .0000005f;
    float count2 = 0;

    float rotationAmount3 = 1f;
    float delaySpeed3 = .0000005f;
    float count3 = 0;
    public static bool state = false; // วฺต้

    void OnTriggerExit(Collider other)
    {
        string latch = "latch_10";
        string handle = "Lock_handle_10";

        if ((other.name) == latch)
        {
            StartCoroutine(SlowSpin());
            state = true;
            Debug.Log(state);
        }

        if ((state == true) && ((other.name) == handle))
        {
            Debug.Log("state = true && handle click");
            StartCoroutine(SlowSpin2());
            StartCoroutine(SlowSpin3());
        }
    }

    IEnumerator SlowSpin()
    {
        GameObject latch_10 = GameObject.Find("latch_10");

        while (count < 45) //89
        {
            latch_10.transform.Rotate(new Vector3(0, rotationAmount, 0));
            count += rotationAmount;
            yield return new WaitForSeconds(delaySpeed);
        }
        latch_10.GetComponent<Rigidbody>().constraints = RigidbodyConstraints.FreezeRotationY;
    }

    IEnumerator SlowSpin2()
    {
        GameObject lever_10 = GameObject.Find("lever_10");

        while (count2 > -63)//120
        {
            lever_10.transform.Rotate(new Vector3(0, -rotationAmount2, 0));
            count2 -= rotationAmount2;
            yield return new WaitForSeconds(delaySpeed2);
        }
        lever_10.GetComponent<Rigidbody>().constraints = RigidbodyConstraints.FreezeRotationY;
    }

    IEnumerator SlowSpin3()
    {
        GameObject door_6 = GameObject.Find("door_6");

        while (count3 < 52)//100
        {
            door_6.transform.Rotate(new Vector3(0, rotationAmount3, 0));
            count3 += rotationAmount3;
            yield return new WaitForSeconds(delaySpeed3);
        }
        door_6.GetComponent<Rigidbody>().constraints = RigidbodyConstraints.FreezeRotationY;
    }

    /* private void Update()
     {
         if (Input.GetMouseButtonDown(0))
         {
             RaycastHit hit;
             Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);

             if (Physics.Raycast(ray, out hit, 100.0f))
             {
                 if (hit.transform != null)
                 {
                     string b = "latch_10";
                     string c = "Lock_handle_10";

                     if ((hit.transform.gameObject.name) == b)
                     {
                         StartCoroutine(SlowSpin());
                         state = true;
                         Debug.Log(state);
                     }

                     if ((state == true) && ((hit.transform.gameObject.name) == c))
                     {
                         Debug.Log("state = true && handle click");
                         StartCoroutine(SlowSpin2());
                         StartCoroutine(SlowSpin3());
                     }
                 }
             }
         }
     }*/
}