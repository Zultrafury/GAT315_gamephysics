#include "body.h"
#include "integrator.h"
#include "raymath.h"

void Body::Step(float dt)
{
    if (type != Type::Dynamic) return;
    
    acl = frc * invMass;

    SemiImplicitIntegrator(*this,dt);
    
    vel *= 1 / (1 + (dt * 0.5f));
}

void Body::Draw(const Scene& scene) const
{
    scene.DrawCircle(pos,size,col);
}

void Body::ApplyForce(const Vector2& force)
{
    frc += force;
}
