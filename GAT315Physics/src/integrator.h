#pragma once
#include "body.h"
#include "raymath.h"

inline void ExplicitIntegrator(Body& body, float dt)
{
    body.pos += body.vel * dt;
    body.vel += body.acl * dt;
}

inline void SemiImplicitIntegrator(Body& body, float dt)
{
    body.vel += body.acl * dt;
    body.pos += body.vel * dt;
}