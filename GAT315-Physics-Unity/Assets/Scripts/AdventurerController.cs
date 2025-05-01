using System.Collections;
using TMPro;
using UnityEngine;

public class AdventurerController : MonoBehaviour
{
    private float movement;
    private bool jump;
    private float airborne = 1f;
    private int jumps;
    private bool facingRight;
    [HideInInspector] public bool swing;
    [HideInInspector] public bool key;
    private Vector3 capturedPos;
    [SerializeField] private TMP_Text retries;
    [SerializeField] private TMP_Text eliminations;
    [SerializeField] private GameObject keyicon;
    [SerializeField] private GameObject winner;
    [SerializeField] private Vector3 respawnPoint;
    [SerializeField] private AudioClip[] sounds;
    [SerializeField] private AudioSource aSource;
    [SerializeField] private int maxjumps;
    [SerializeField] private float speed = 2;
    [SerializeField] private BoxCollider2D footColl;
    [SerializeField] private CapsuleCollider2D capColl;
    [SerializeField] private BoxCollider2D swordColl;
    [SerializeField] private Animator aCont;

    private Rigidbody2D rb;

    private static readonly int Movement = Animator.StringToHash("Movement");
    private static readonly int Airborne = Animator.StringToHash("Airborne");
    private static readonly int Swing = Animator.StringToHash("Swing");

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
        capturedPos = transform.position;
    }

    // Update is called once per frame
    void Update()
    {
        // ANIMATOR VARS
        aCont.SetFloat(Movement, Mathf.Abs(movement));
        aCont.SetFloat(Airborne, airborne);
        aCont.SetBool(Swing, swing);

        // SWORD SWING LOGIC
        if (swing)
        {
            var enemy = Physics2D.BoxCastAll(swordColl.bounds.center, swordColl.size,
                0f, Vector2.up, 0f, LayerMask.GetMask("Enemy"));
            foreach (var e in enemy)
            {
                Destroy(e.transform.gameObject);
                string text = eliminations.text;
                string lasttext = text.ToCharArray()[text.Length - 1].ToString();
                eliminations.text = "Eliminations: "+(int.Parse(lasttext)+1);
            }
            
            var shell = Physics2D.BoxCastAll(swordColl.bounds.center, swordColl.size,
                0f, Vector2.up, 0f, LayerMask.GetMask("Shell"));
            foreach (var s in shell)
            {
                s.rigidbody.AddForce(Random.insideUnitCircle*20,ForceMode2D.Impulse);
            }
        }
        else // SUPPRESS INPUTS WHILE SWINGING
        {
            movement = Input.GetAxisRaw("Horizontal");
            jump = Input.GetKeyDown(KeyCode.Space);
        }
        // HANDLE CONDITIONS FOR SWINGING
        if (Input.GetKeyDown(KeyCode.LeftShift) && !swing && Mathf.Approximately(airborne, 0.5f))
        {
            swing = true;
            PlaySound(sounds[1],0.2f);
            StartCoroutine(SwordSwing());
        }
        // CHECK FOR INTERACTIBLE OBJECTS IN COLLIDER
        var interact = Physics2D.CapsuleCastAll(capColl.bounds.center, capColl.size, CapsuleDirection2D.Vertical, 
            0f, Vector2.up, 0f, LayerMask.GetMask("Interactible"));
        foreach (var i in interact)
        {
            var obj = i.transform.gameObject;
            if (obj.CompareTag("Key"))
            {
                Destroy(obj);
                PlaySound(sounds[2],0.6f);
                key = true;
                keyicon.SetActive(true);
            }

            if (key && obj.CompareTag("Chest"))
            {
                winner.SetActive(true);
            }
            
            if (obj.CompareTag("Spikes"))
            {
                TakeDamage();
            }
        }
        
        // CHECK FOR ENEMIES
        var enemies = Physics2D.CapsuleCast(capColl.bounds.center, capColl.size, CapsuleDirection2D.Vertical, 
            0f, Vector2.up, 0f, LayerMask.GetMask("Enemy"));
        if (enemies)
        {
            TakeDamage();
        }
        // HANDLE TERRAIN COLLISION ABOVE FEET
        var collision = Physics2D.CapsuleCast(capColl.bounds.center, capColl.size, CapsuleDirection2D.Vertical, 
            0f, Vector2.up, 0f, LayerMask.GetMask("PlayerCollision"));
        if (collision)
        {
            transform.position = capturedPos;
            airborne = 0.7f;
        }
        
        // HANDLE TURNING
        if (movement != 0)
        {
            facingRight = movement > 0;
        }
        transform.rotation = Quaternion.Euler(0, facingRight ? 0 : 180, 0);
        
        // COLLISION ROLLBACK
        capturedPos = transform.position;
    }

    private void FixedUpdate()
    {
        // UPDATE LERP VAR
        airborne += 1f * Time.fixedDeltaTime;
        // HANDLE COLLISIONS AT FEET
        var hit = Physics2D.Raycast(footColl.bounds.center,Vector2.down,footColl.bounds.size.y,LayerMask.GetMask("PlayerCollision"));
        if (hit && airborne > 0.05)
        {
            rb.linearVelocity = (movement * speed) * new Vector2(hit.normal.y, -hit.normal.x);
            airborne = 0.5f;
            jumps = maxjumps;
        }
        else // GRAVITY/JUMP WITH LERP FUNCTION
        {
            rb.linearVelocityX = (movement * speed);
            rb.linearVelocityY = Mathf.Lerp(20, -20, airborne);
        }
        
        // HANDLE CONDITIONS FOR JUMPING
        if (jump && jumps > 0 && airborne > 0.1f)
        {
            PlaySound(sounds[0]);
            jumps--;
            airborne = 0f;
        }
    }

    void PlaySound(AudioClip clip, float volume = 1f) // PLAY SOUNDS AT PLAYER OBJECT
    {
        aSource.clip = clip;
        aSource.volume = volume;
        aSource.Play();
    }

    IEnumerator SwordSwing() // HANDLE INPUT TIMEOUT FOR SWINGING
    {
        yield return new WaitForSeconds(0.2f);
        swing = false;
    }

    private void TakeDamage() // HANDLE TAKING DAMAGE
    {
        transform.position = respawnPoint;
        string text = retries.text;
        string lasttext = text.ToCharArray()[text.Length - 1].ToString();
        retries.text = "Retries: "+(int.Parse(lasttext)+1);
    }
}
