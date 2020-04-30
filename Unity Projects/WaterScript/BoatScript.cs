using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BoatScript : MonoBehaviour
{

    public float speed = 1.0f; //sebesseg
    public float acceleration = 1.0f; //gyorsulas
    public float maxspeed = 2.0f;//maxsebesseg
    public float minspeed = -0.25f;    //minsebesseg
    public float rudderDelta = 2.0f; //dolesszog
    public float maxRudder = 6.0f; //maxbedoles
    public float bob = 0.1f; //hompolyges
    public float bobFrequency = 0.2f; //hompolyges gyorsasaga

    private float elapsed = 0.0f;
    private float seaLevel = 0.0f;
    private float heading = 0.0f; //merretart
    private float rudder = 0.0f; //doles



    void Bobbing()
    {
        Vector3 temp = transform.position;

        elapsed += Time.deltaTime;
        temp.y = seaLevel + bob * Mathf.Sin(elapsed * bobFrequency * (Mathf.PI * 2));
        transform.position = temp;

    }

    void Steering()
    {
        if (Input.GetAxisRaw("Horizontal") != 0)
        {
            rudder += Input.GetAxisRaw("Horizontal") * rudderDelta * Time.deltaTime;
        }
        else if ( (rudder >= 0 && Input.GetAxisRaw("Horizontal") == 0) && (UnityEditor.TransformUtils.GetInspectorRotation(transform).z <= -1))
        rudder -= rudderDelta * Time.deltaTime;
        else if ((rudder <= 0 && Input.GetAxisRaw("Horizontal") == 0) && (UnityEditor.TransformUtils.GetInspectorRotation(transform).z >=1))
               rudder += rudderDelta * Time.deltaTime;

        if (rudder > maxRudder)
        {
            rudder = maxRudder;
        }
        else if (rudder < -maxRudder)
        {
            rudder = -maxRudder;
        }

        heading = (heading + rudder * Time.deltaTime) % 360;
        transform.eulerAngles = new Vector3(0, heading, -rudder);


    }

    void Sailing()
    {
        speed += Input.GetAxis("Vertical") * acceleration * Time.deltaTime;
        if (speed > maxspeed)
        {
            speed = maxspeed;
        }
        else if (speed < minspeed)
        {
            speed = minspeed;
        }
        transform.Translate(0, 0, speed * Time.deltaTime);

    }

    void Update()
    {
        Bobbing();
        Steering();
        Sailing();  
    }

    void Awake()
    {
        seaLevel = transform.position.y;
    }

}