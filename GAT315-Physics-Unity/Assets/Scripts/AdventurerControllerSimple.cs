using System;
using UnityEngine;

public class AdventurerControllerSimple : MonoBehaviour
{
    [SerializeField] private float speed = 2;
    private float movement;
    private bool jump;
    private Rigidbody2D rb;
    private bool facingRight;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
    }

    // Update is called once per frame
    void Update()
    {
        movement = Input.GetAxisRaw("Horizontal");
        jump = Input.GetKeyDown(KeyCode.Space);
        if (movement != 0)
        {
            facingRight = movement > 0;
        }
        transform.rotation = Quaternion.Euler(0, facingRight ? 0 : 180, 0);
    }

    private void FixedUpdate()
    {
        rb.linearVelocityX = 0;
        rb.AddForce(new Vector2(movement * speed,0),ForceMode2D.Impulse); // HORIZONTAL MOVEMENT
    }
}
