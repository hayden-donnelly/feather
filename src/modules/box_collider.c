#include <stdio.h>
#include "box_collider.h"

static int number_of_box_colliders;
static Box_Collider *box_colliders = NULL;

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
    for(int i = 0; i < number_of_box_colliders; i++)
    {
        if(&box_colliders[i] == NULL || box_colliders[i].active == 0)
        {
            col->active = 1;
            box_colliders[i] = *col;
            return;
        }
    }
}

void box_collider_remove(Box_Collider *col)
{
    col->active = 0;
}

void box_collider_init_module(int max_box_colliders)
{
    if(box_colliders == NULL)
    {
        box_colliders = malloc(sizeof(Box_Collider) * max_box_colliders);
        number_of_box_colliders = max_box_colliders;
    }
    else
    {
        printf("Box colliders already initialized\n");
    }
}

void box_collider_cleanup_module(void)
{
    free(box_colliders);
}