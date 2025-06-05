#pragma once
#include <vector>
#include "contact.h"
#include "raylib.h"
#include "scene.h"

using contacts_t = std::vector<Contact>;

struct Body;
struct Spring;

class World
{
public:
    ~World();

    void Initialize(Vector2 gravity = Vector2{0, -9.81f}, size_t poolSize = 32);

    Body* CreateBody(const Vector2& position, float size, const Color& color);
    Body* CreateBody(const Vector2& position, float mass, int type, float size = 0.25f, float damping = 0.5f,
                     const Color& color = WHITE, float restitution = 0.5f);
    Spring* CreateSpring(Body* body_a, Body* body_b, float restlength, float stiffness, float damping);
    void Step(float dt);
    void Draw(const Scene& scene);
    void DestroyAll() const;

    std::vector<Body*>& GetBodies() { return m_bodies; }

    Vector2 m_gravity;

private:
    std::vector<Body*> m_bodies;
    std::vector<Spring*> m_springs;
    contacts_t m_contacts;
};
