#pragma once
#include "utils.h"

typedef struct Transform Transform;
struct Transform
{
    Transform *parent;
    // Offset from origin/parent
    Vec2_Int pos;
};
Transform transform_set(int x, int y, Transform *parent);