#include "box_collider.h"

Box_Collider box_collider_init(int w, int h, Transform col_transform)
{
    Box_Collider new_box_collider;
    new_box_collider.active = 1;
    new_box_collider.transform = col_transform;
    new_box_collider.w = w;
    new_box_collider.h = h;
    return new_box_collider;
}

void box_collider_add(Box_Collider *col)
{
    for(int i = 0; i < MAX_BOX_COLLIDERS; i++)
    {
        if(box_colliders[i] == NULL || box_colliders[i]->active == 0)
        {
            col->active = 1;
            box_colliders[i] = col;
            return;
        }
    }
}

void box_collider_remove(Box_Collider *col)
{
    col->active = 0;
}