#pragma once
#include "raymath.h"

struct Polar
{
public:
    Polar() = default;
    Polar(float angle, float radius) :
        angle{ angle },
        radius{ radius }
    {
    }

    Polar(const Vector2& v) :
        angle{Vector2Angle(v,Vector2{1,0})},
        radius{Vector2Length(v)}
    {
    }

    Polar& operator = (const Vector2& v)
    {
        angle = Vector2Angle(v,Vector2{1,0});
        radius = Vector2Length(v);

        return *this;
    }

    operator Vector2() const
    {
        Vector2 v;
        v.x = cos(angle)* radius;
        v.y = sin(angle)* radius;

        return v;
    }

public:
    float angle{ 0 };
    float radius{ 0 };
};
