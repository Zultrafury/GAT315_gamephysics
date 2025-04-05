using UnityEngine;

public class PlayerController : MonoBehaviour
{
    [SerializeField] float speed = 1;
    [SerializeField] float accel = 1;
    [SerializeField] float jumpheight = 2;
    [SerializeField] LayerMask layermask = Physics.AllLayers;
    
    Rigidbody rb;
    Vector3 force;
    
    void Start() {
        rb = GetComponent<Rigidbody>();
    }

    void Update() {
        Vector3 direction = Vector3.zero;
        direction.x = Input.GetAxis("Horizontal");
        direction.z = Input.GetAxis("Vertical");
        
        force = direction * accel;

        if (Input.GetKeyDown(KeyCode.Space)) {
            float jumpscale = Mathf.Sqrt(-2 * jumpheight * Physics.gravity.y);
            rb.AddForce(Vector3.up * jumpscale, ForceMode.Impulse);
        }
        
        var colliders = Physics.OverlapSphere(transform.position, 2, layermask);
        foreach (var col in colliders) {
            Destroy(col.gameObject);
        }

        Debug.DrawRay(transform.position, transform.forward * 5, Color.magenta);
        if (Physics.Raycast(transform.position, transform.forward, out RaycastHit hit, 5, layermask)) {
            Destroy(hit.collider.gameObject);
        }
    }

    void FixedUpdate() {
        rb.AddForce(force * 10);
        Vector3 linmov = new Vector3(rb.linearVelocity.x, 0, rb.linearVelocity.z);
        if (linmov.magnitude > speed) {
            rb.linearVelocity = new Vector3(linmov.normalized.x * speed, rb.linearVelocity.y, linmov.normalized.z * speed);
        }
    }

    void OnDrawGizmosSelected() {
        Gizmos.color = Color.red;
        Gizmos.DrawWireSphere(transform.position, 2);
    }
}
