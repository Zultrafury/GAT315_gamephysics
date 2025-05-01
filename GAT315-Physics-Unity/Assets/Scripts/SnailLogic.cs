using System;
using UnityEngine;
using Random = UnityEngine.Random;

public class SnailLogic : MonoBehaviour
{
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    [SerializeField] Transform target;
    [SerializeField] private float speed = 0.05f;
    [SerializeField] private GameObject gib;
    private Vector3 start;
    private Vector3 end;
    private bool tostart;
    void Start()
    {
        start = transform.position;
        end = target.position;
    }

    // Update is called once per frame
    void Update()
    {
        float direction = tostart ? speed : -speed;
        if (transform.position.x <= end.x)
        {
            tostart = true;
            transform.rotation = Quaternion.Euler(0, 180, 0);
        }
        if (transform.position.x >= start.x)
        {
            tostart = false;
            transform.rotation = Quaternion.Euler(0, 0, 0);
        }
        transform.position += new Vector3(direction, 0, 0);
    }

    private void OnDestroy()
    {
        var shell = Instantiate(gib,transform.position,transform.rotation);
        shell.GetComponent<Rigidbody2D>().AddForce(Random.insideUnitCircle*20,ForceMode2D.Impulse);
        Destroy(gameObject);
    }
}
