#pragma once
#include "scene.h"

struct Spring
{
public:
    Spring() = default;
    Spring(Body* body_a, Body* body_b, float restlength, float stiffness, float damping) :
    m_body_a{body_a},
    m_body_b{body_b},
    m_damping{damping},
    m_stiffness{stiffness},
    m_restlength{restlength}
    {}
    
    void ApplySpringForce(float damping, float mult = 1);
    void ApplySpringForce(float mult = 1);
    void Draw(const Scene& scene) const;
    
private:
    Body* m_body_a;
    Body* m_body_b;
    float m_damping;
    float m_stiffness;
    float m_restlength;
};
