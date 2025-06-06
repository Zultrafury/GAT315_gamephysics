#include "world.h"
#include "spring.h"
#include "body.h"
#include "collision.h"

World::~World()
{
    DestroyAll();
}

void World::Initialize(Vector2 gravity, size_t poolSize)
{
    m_gravity = gravity;
    m_bodies.reserve(poolSize);
}

Body* World::CreateBody(const Vector2& position, float size, const Color& color)
{
    Body* body = new Body(position, size, color);
    m_bodies.push_back(body);

    return body;
}

Body* World::CreateBody(const Vector2& position, float mass, int type, float size, float damping, const Color& color, float restitution)
{
    Body* body = new Body(position, mass, static_cast<Body::Type>(type), size, damping, color, restitution);
    m_bodies.push_back(body);

    return body;
}

Spring* World::CreateSpring(Body* body_a, Body* body_b, float restlength, float stiffness, float damping)
{
    Spring* spring = new Spring(body_a, body_b, restlength, stiffness, damping);
    m_springs.push_back(spring);

    return spring;
}

void World::Step(float dt)
{
    for (size_t i = 0; i < m_bodies.size(); i++)
    {
        Body* body = m_bodies[i];
        body->ApplyGravity(m_gravity);
        body->Step(dt);
        body->ClearForce();
        if (body->delme) m_bodies.erase(m_bodies.begin() + i);
    }
    
    for (auto spring : m_springs)
    {
        spring->ApplySpringForce();
    }

    m_contacts.clear();
    CreateContacts(m_bodies, m_contacts);
    SeparateContacts(m_contacts);
    for (int i = 0; i < 3; ++i)
    {
        ResolveContacts(m_contacts);
    }
}

void World::Draw(const Scene& scene)
{
    for (auto body : m_bodies)
    {
        body->Draw(scene);
    }
    for (auto spring : m_springs)
    {
        spring->Draw(scene);
    }
}

void World::DestroyAll() const
{
    for (auto spring : m_springs)
    {
        delete spring;
    }
    for (auto body : m_bodies)
    {
        delete body;
    }
}
