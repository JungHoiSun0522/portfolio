using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class run : MonoBehaviour
{
    // Start is called before the first frame update
    public bool ready;
    public Transform target;
    private NavMeshAgent agent;
    public bool hide;
    public float HideTime;

    void Start()
    {
        agent = GetComponent<NavMeshAgent>();
    }

    // Update is called once per frame
    void Update()
    {
        if(ready == true) {
            // transform.LookAt(target);
            //transform.position = Vector3.MoveTowards(transform.position, target.position, speed * Time.deltaTime);
            agent.SetDestination(target.position);
            if (hide == false) {
                Invoke("Hiding", HideTime); 
                hide = true;
            }
            
        }
    }

    void Hiding(){
        gameObject.SetActive(false);
        if(gameObject.name == "M9")
        {
            GameObject.Find("M9").GetComponent<Ending>().state = false;
        }
    }
}
