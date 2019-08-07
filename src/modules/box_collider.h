#pragma once
#include "transform.h"
#include <stdlib.h>

#define MAX_BOX_COLLIDERS 500

typedef struct Box_Collider
{
    int active;
    Transform transform;
    int w, h;
} Box_Collider;
Box_Collider init_box_collider(int w, int h, Transform col_transform);
void subscribe_to_box_colliders(Box_Collider *desired_box_collider);

Box_Collider *box_colliders[MAX_BOX_COLLIDERS];