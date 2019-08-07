#pragma once

typedef struct Transform Transform;
struct Transform
{
    Transform *parent;
    // Offset from origin/parent
    int x, y;
};
Transform transform_set(int x, int y, Transform *parent);