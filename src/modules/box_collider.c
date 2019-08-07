#include "box_collider.h"

Box_Collider init_box_collider(int w, int h, Transform col_transform)
{
    Box_Collider new_box_collider;
    new_box_collider.active = 1;
    new_box_collider.transform = col_transform;
    new_box_collider.w = w;
    new_box_collider.h = h;
    return new_box_collider;
}

void subscribe_to_box_colliders(Box_Collider *desired_box_collider)
{
    for(int i = 0; i < MAX_BOX_COLLIDERS; i++)
    {
        if(box_colliders[i] == NULL || box_colliders[i]->active == 0)
        {
            box_colliders[i] = desired_box_collider;
            return;
        }
    }
}