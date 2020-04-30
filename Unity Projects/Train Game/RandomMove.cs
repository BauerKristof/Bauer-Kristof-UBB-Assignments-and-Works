using System.Collections;
using System.Collections.Generic;
using System.Threading.Tasks;
using UnityEngine;
using UnityEngine.SceneManagement;

public class RandomMove : MonoBehaviour
{
    [SerializeField]
    Vector3 newPosition;
    [SerializeField]
    Transform playerObj;
    [SerializeField]
    float smoothing = 1f;

    public int waitNumb;
    private bool runedOnce = false;

    void Start()
    {

        waitNumb = Random.Range(1, 4);
        newPosition.x = transform.position.x;
        newPosition.y = transform.position.y;

    }

    void Update()
    {

        if ((Mathf.Abs(playerObj.position.x - transform.position.x) < 3f) && (runedOnce == false))
        {
            Invoke("callTimedCorutine", waitNumb);
        }
    }

    void callTimedCorutine()
    {
        runedOnce = true;
        StartCoroutine(MoveObstacle());
    }

    IEnumerator MoveObstacle()
    {
        while (Vector3.Distance(transform.position, newPosition) > 0.05f)
        {
            transform.position = Vector3.Lerp(transform.position, newPosition, smoothing * Time.deltaTime);
            yield return null;
        }
    }

    void OnCollisionEnter(Collision collision)
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }
}
