#include "body.h"
#include "raymath.h"

void Body::Step(float dt)
{
    pos += vel * dt;
}

void Body::Draw(const Scene& scene) const
{
    scene.DrawCircle(pos,size,col);
}
