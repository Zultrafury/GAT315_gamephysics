#pragma once
#include <vector>
#include "raylib.h"
#include "scene.h"

struct Body;

class World
{

public:
    ~World();

    void Initialize(Vector2 gravity = Vector2{0, -9.81f}, size_t poolSize = 32);

    Body* CreateBody(const Vector2& position, float size, const Color& color);
    Body* CreateBody(const Vector2& position, float mass, int type, float size = 0.25f, float damping = 0.5f, const Color& color = WHITE);
    void Step(float dt);
    void Draw(const Scene& scene);
    void DestroyAll();

    std::vector<Body*>& GetBodies() { return m_bodies; }

    Vector2 m_gravity;
private:
    std::vector<Body*> m_bodies;
};
