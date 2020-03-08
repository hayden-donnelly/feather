#pragma once
#include "../../component.h"
#include "collision_info.h"

typedef struct
{
    int entity_id;
    int x, y;
    int w, h;
    int is_trigger;
} Box_Collider;

Collision_Info box_collision(Component_Type *colliders, Component_Type *position, Box_Collider *active_collider, 
                            int move_x, int move_y, unsigned int collision_ids_length);