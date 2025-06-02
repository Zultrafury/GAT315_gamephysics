#pragma once
#include "vector_scene.h"

struct Contact
{
    Body* bodyA;
    Body* bodyB;

    float restitution;	// restitution of both bodies
    float depth;		// penetration depth
    Vector2 normal;		// normal contact vector
};
