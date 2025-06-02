#include "collision.h"
#include "body.h"
#include "mathutils.h"
#include "raymath.h"

bool Intersects(const Body* bodyA, const Body* bodyB)
{
    float distance = Vector2Distance(bodyA->pos,bodyB->pos);
    float radius = bodyA->size + bodyB->size;

    return (distance <= radius);
}

void CreateContacts(const bodies_t& bodies, contacts_t& contacts)
{
    for (size_t i = 0; i < bodies.size(); i++)
    {
        Body* bodyA = bodies[i];
        for (size_t j = i + 1; j < bodies.size(); j++)
        {
            Body* bodyB = bodies[j];
            if (bodyA->type != Body::Type::Dynamic && bodyB->type != Body::Type::Dynamic) continue;

            if (Intersects(bodyA, bodyB))
            {
                Contact contact;
                contact.bodyA = bodyA;
                contact.bodyB = bodyB;

                Vector2 direction = bodyB->pos - bodyA->pos;
                float distanceSqr = Vector2Length(direction);
                if (distanceSqr <= EPSILON)
                {
                    direction = Vector2{ randomf(-0.05f, 0.05f), randomf(-0.05f, 0.05f) };
                    distanceSqr = Vector2LengthSqr(direction);
                }

                float distance = sqrt(distanceSqr);
                float radius = bodyA->size + bodyB->size;
                contact.depth = (radius) - distance;
                contact.normal = Vector2Normalize(direction);
                contact.restitution = (bodyA->damping + bodyB->damping) / 2;

                contacts.push_back(contact);
            }
        }
    }
}

void SeparateContacts(const contacts_t& contacts)
{
    for (auto contact : contacts)
    {
        float totalInverseMass = contact.bodyA->invMass + contact.bodyB->invMass;
        Vector2 separation = contact.normal * (contact.depth / totalInverseMass);
        contact.bodyA->pos = contact.bodyA->pos + (separation * contact.bodyA->invMass);
        contact.bodyB->pos = contact.bodyB->pos - (separation * contact.bodyB->invMass);
    }
}