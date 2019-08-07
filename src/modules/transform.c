#include "transform.h"

Transform transform_set(int x, int y, Transform *parent)
{
    Transform new_transform;
    new_transform.parent = parent;
    new_transform.x = x;
    new_transform.y = y;
    return new_transform;
}