#pragma once
#include "raylib.h"

struct AABB
{
    Vector2 center;
    Vector2 size;

    AABB(const Vector2& center, const Vector2& size) :
    size(size),
    center(center)
    {}

    Vector2 extents() const { return Vector2{size.x * 0.5f, size.y * 0.5f}; }
    Vector2 min() const { return Vector2{center.x - extents().x,center.y - extents().y}; }
    Vector2 max() const { return Vector2{center.x + extents().x,center.y + extents().y}; }
};
