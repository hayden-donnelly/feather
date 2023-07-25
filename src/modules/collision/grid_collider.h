#pragma once
//#include "box_collider.h"
#include "../../component.h"
#include "collision_info.h"

typedef struct
{
    int entity_id;
    // Width of the grid in cells.
    unsigned int grid_width;
    // Height of the grid in cells.
    unsigned int grid_height;
    unsigned int cell_width;
    unsigned int cell_height;
    int *collision_ids;
} Grid_Collider;

Collision_Info simple_grid_collision(
    Component_Type *grid_collider, Component_Type *position, 
    int move_x, int move_y, int position_id, int grid_collider_id
);

Collision_Info complex_grid_collision(
    Component_Type *grid_collider_type, Component_Type *position_type, 
    Component_Type *box_collider_type, int move_x, int move_y, int mover_id, 
    int grid_collider_id
);

Collision_Info perfect_grid_collision(
    Component_Type *grid_collider_type, Component_Type *position_type, 
    Component_Type *box_collider_type, int move_x, int move_y, int mover_id, 
    int grid_collider_id
);