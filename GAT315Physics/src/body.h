#pragma once
#include "AABB.h"
#include "raylib.h"
#include "raymath.h"
#include "scene.h"

struct Body
{
public:
    enum class Type
    {
        Dynamic,
        Static,
        Kinematic
    };

    enum class ForceMode
    {
        Force,
        Impulse
    };

public:
    Body() = default;

    Body(const Vector2& position, const Vector2& velocity, float size = 0.25f, const Color& color = WHITE) :
        pos{position},
        vel{velocity},
        size{size},
        col{color}
    {
    }

    Body(const Vector2& position, float mass, Type type, float size = 0.25f, float damping = 0.5f,
         const Color& color = WHITE) :
        pos{position},
        type{type},
        size{size},
        damping{damping},
        col{color},
        mass{mass}
    {
        invMass = (type == Type::Dynamic) ? 1 / mass : 0;
    }

    Body(const Vector2& position, const Vector2& velocity, const Color& color = WHITE) :
        Body(position, velocity, 0.25f, color)
    {
    }

    Body(const Vector2& position, float size, const Color& color = WHITE) :
        Body(position, Vector2{0, 0}, size, color)
    {
    }

    void Step(float dt);
    void Draw(const Scene& scene) const;

    void ApplyForce(const Vector2& force, ForceMode mode = ForceMode::Force);
    void ApplyGravity(const Vector2& gravity) { frc += (gravity * gravScale) * mass; }
    void ClearForce() { frc = Vector2{0, 0}; }
    AABB GetAABB() const { return AABB{ pos, { size * 2, size * 2 } }; }

    Vector2 pos{0, 0};
    Vector2 vel{0, 0};
    Vector2 acl{0, 0};
    Vector2 frc{0, 0};
    Type type{Type::Dynamic};
    float size;
    float damping = 0.5f;
    Color col;
    float mass{1};
    float invMass{1};

    float gravScale{1};

    Body* next = nullptr;
    Body* prev = nullptr;
};
