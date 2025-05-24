#include "world.h"
#include "spring.h"
#include "body.h"

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

Body* World::CreateBody(const Vector2& position, float mass, int type, float size, float damping, const Color& color)
{
    Body* body = new Body(position, mass, static_cast<Body::Type>(type), size, damping, color);
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
    for (auto body : m_bodies)
    {
        body->ApplyGravity(m_gravity);
        body->Step(dt);
        body->ClearForce();
    }
    for (auto spring : m_springs)
    {
        spring->ApplySpringForce();
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

void World::DestroyAll()
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
