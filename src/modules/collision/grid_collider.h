#pragma once
//#include "box_collider.h"
#include "../../component.h"
#include "collision_info.h"

typedef struct
{
    int entity_id;
    unsigned int grid_width;
    unsigned int grid_height;
    unsigned int cell_width;
    unsigned int cell_height;
    int *collision_ids;
} Grid_Collider;

Collision_Info grid_collision(Component_Type *grid_collider, Component_Type *position, 
                        Box_Collider *box_collider, int move_x, int move_y);