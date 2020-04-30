using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(FloatObject))]
public class BoatControllerScript : MonoBehaviour {
    public Vector3 COM;
    [Space(15)]
    public float speed = 1.0f;
    public float steerSpeed = 1.0f;
    public float movementThresold = 10.0f;
    public float floatHeight = 2.0f;

    private Vector3 position;

    Transform m_COM;
    float verticalInput;
    float movementFactor;
    float horizontalInput;
    float steerFactor;

    // Update is called once per frame


    void Update()
    {

        Movement();
        Steer();
        disableFly();
        Balance();

    }

    void Balance() {
        if (!m_COM)
        {
            m_COM = new GameObject("COM").transform;
            m_COM.SetParent(transform);

        }

        m_COM.position = COM;
        GetComponent<Rigidbody>().centerOfMass = m_COM.position;
    }

    void Movement() {
        verticalInput = Input.GetAxis("Vertical");
        movementFactor = Mathf.Lerp(movementFactor, verticalInput, Time.deltaTime / movementThresold);
        transform.Translate(0.0f, 0.0f, movementFactor * speed);
       /* if (UnityEditor.TransformUtils.GetInspectorRotation(transform).x > -8.0f)
        { transform.Rotate(Time.deltaTime * 2 f, 0.0f, 0.0f);
            Debug.Log(Time.deltaTime);
        }*/
    }

    void Steer()
    {
        horizontalInput = Input.GetAxis("Horizontal");
        steerFactor = Mathf.Lerp(steerFactor, horizontalInput * verticalInput, Time.deltaTime / movementThresold);

        float xRot = UnityEditor.TransformUtils.GetInspectorRotation(transform).x;
        

        if (horizontalInput > 0) {transform.Rotate(0.0f, steerFactor * steerSpeed, steerFactor * 1f); }
        else { transform.Rotate(0.0f, steerFactor * steerSpeed, steerFactor * -1f); }
    }

    void disableFly()
    {
        Vector3 temp = transform.position;
        float xRot = UnityEditor.TransformUtils.GetInspectorRotation(transform).x;
        float zRot = UnityEditor.TransformUtils.GetInspectorRotation(transform).z;

        if (((xRot <= -20f) || (xRot >= 35f)) || ((zRot <= -50f) || (zRot >=50f)))
        {
            speed = 0f;
            GetComponent<FloatObject>().enabled = false;
            Debug.Log("Ittkapta el");

        }


    }
}
