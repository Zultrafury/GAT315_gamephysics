#include "body.h"
#include "raymath.h"

void Body::Step(float dt)
{
    pos += vel * dt;
    vel *= 1 / (1 + (dt * 0.5f));
}

void Body::Draw(const Scene& scene) const
{
    scene.DrawCircle(pos,size,col);
}
