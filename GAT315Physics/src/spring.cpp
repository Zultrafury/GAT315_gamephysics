#include "spring.h"

#include "body.h"
#include "scene.h"

void Spring::ApplySpringForce(float mult)
{
    float damping = m_damping;
    // Step 1: Calculate direction vector from bodyB to bodyA
    Vector2 direction = m_body_a->pos - m_body_b->pos;
    float lengthSquared = Vector2LengthSqr(direction);
    if (lengthSquared <= EPSILON) return;

    // Step 2: Calculate spring displacement
    float length = sqrtf(lengthSquared);
    float displacement = length - m_restlength;  // Stretching if > 0, compressed if < 0

    // Step 3: Apply Hooke's Law: F = -k * x
    float forceMagnitude = -(m_stiffness * mult) * displacement;

    // Step 4: Normalize direction and calculate spring force vector
    Vector2 normalizedDirection = direction / length;
    Vector2 springForce = normalizedDirection * forceMagnitude;

    // Step 5: Dampen the spring to reduce oscillation
    Vector2 velocityDifference = m_body_a->vel - m_body_b->vel;
    float dampingAmount = Vector2DotProduct(velocityDifference, normalizedDirection) * damping;
    Vector2 dampingForce = normalizedDirection * dampingAmount;

    // Subtract damping from spring force
    Vector2 totalForce = springForce - dampingForce;

    // Step 6: Apply equal and opposite forces to the two bodies
    m_body_a->ApplyForce(totalForce);
    m_body_b->ApplyForce(Vector2Negate(totalForce));
}

void Spring::Draw(const Scene& scene) const
{
    scene.DrawLine(m_body_a->pos,m_body_b->pos,WHITE);
}
