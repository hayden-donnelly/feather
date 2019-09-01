#pragma once
#include "transform.h"
#include <stdlib.h>

typedef struct Box_Collider
{
    int active;
    Transform transform;
    int w, h;
} Box_Collider;

Box_Collider box_collider_init(int w, int h, Transform col_transform);
void box_collider_add(Box_Collider *col);
void box_collider_remove(Box_Collider *col);
void box_collider_module_init(const int max_box_colliders);
void box_collider_cleanup_module(void);