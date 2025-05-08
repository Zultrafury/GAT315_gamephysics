#pragma once
#include "raylib.h"
#include "scene.h"

struct Body
{
public:
    Body() = default;
    Body(const Vector2& position, const Vector2& velocity, float size = 0.25f, const Color& color = WHITE) :
        pos{position},
        vel{velocity},
        size{size},
        col{color}
    {}
    Body(const Vector2& position, const Vector2& velocity, const Color& color = WHITE) :
        Body(position,velocity,0.25f,color)
    {}
    Body(const Vector2& position, float size, const Color& color = WHITE) :
        Body(position,Vector2{0,0},size,color)
    {}

    void Step(float dt);
    void Draw(const Scene& scene) const;
    
    Vector2 pos;
    Vector2 vel;
    float size;
    Color col;

    Body* next = nullptr;
    Body* prev = nullptr;
};
