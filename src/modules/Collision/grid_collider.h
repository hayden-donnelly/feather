#pragma once

typedef struct
{
    int entity_id;
    unsigned int grid_width;
    unsigned int grid_height;
    int *collision_ids;
} Grid_Collider;