#include "body.h"
#include "integrator.h"
#include "raymath.h"

void Body::Step(float dt)
{
    switch (type) {
    case Type::Static:
        return;
    case Type::Kinematic:
        SemiImplicitIntegrator(*this, dt);
        break;
    case Type::Dynamic:
        acl = frc * invMass;

        SemiImplicitIntegrator(*this, dt);

        vel *= 1 / (1 + (dt * damping));
        break;
    }
}

void Body::Draw(const Scene& scene) const
{
    scene.DrawCircle(pos, size, col);
}

void Body::ApplyForce(const Vector2& force, ForceMode mode)
{
    if (type != Type::Dynamic) return;
    if (mode == ForceMode::Force)
    {
        frc += force;
    }
    else if (mode == ForceMode::Impulse)
    {
        vel += force;
    }
}
