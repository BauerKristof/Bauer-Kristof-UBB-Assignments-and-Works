using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AddPlayerControlled : MonoBehaviour
{
    [SerializeField]
    Vector3 fixedSpeed;

    [SerializeField]
    KeyCode keyPositive;
    [SerializeField]
    KeyCode keyNegative;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        if(Input.GetKey(keyPositive))
            {
            GetComponent<Rigidbody>().velocity += fixedSpeed;
            }

        if (Input.GetKey(keyNegative))
        {
            GetComponent<Rigidbody>().velocity -= fixedSpeed;
        }
    }
}
