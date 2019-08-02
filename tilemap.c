#include "tilemap.h"

// Checks collision on the desired movement and returns
//  modified movement if necessary to avoid clipping.
Vec2_Int tile_map_collision(const Vec2_Int *movement, const Box_Collider *col, const Tile_Map *tile_map)
{
    Vec2_Int move_sign;
    move_sign.x = (int)copysign(1, movement->x);
    move_sign.y = (int)copysign(1, movement->y);

    Vec2_Int col_grid_pos1;     // top left corner
    Vec2_Int col_grid_pos2;     // bottom right corner
    Vec2_Int modified_movement;

    // y collision
    for(modified_movement.y = 0; modified_movement.y != movement->y && movement->y != 0; 
        modified_movement.y += move_sign.y)
    {
        col_grid_pos1.x = (col->transform.x + modified_movement.x) / tile_map->tile_set->tile_width;
        col_grid_pos2.x = (col->transform.x + modified_movement.x + col->w) / tile_map->tile_set->tile_width;
        col_grid_pos1.y = (col->transform.y + modified_movement.y) / tile_map->tile_set->tile_height;
        col_grid_pos2.y = (col->transform.y + modified_movement.y + col->h) / tile_map->tile_set->tile_height;
    
        if(move_sign.y < 0
            && (tile_map->collision_map[col_grid_pos1.y * tile_map->map_width + col_grid_pos1.x] != 0
            || tile_map->collision_map[col_grid_pos1.y * tile_map->map_width + col_grid_pos2.x] != 0))
        {
            modified_movement.y -= move_sign.y;
            break;
        }
        else if(move_sign.y > 0
            && (tile_map->collision_map[col_grid_pos2.y * tile_map->map_width + col_grid_pos1.x] != 0
            || tile_map->collision_map[col_grid_pos2.y * tile_map->map_width + col_grid_pos2.x] != 0))
        {
            modified_movement.y -= move_sign.y;
            break;
        }
    }

    // x collision
    for(modified_movement.x = 0; modified_movement.x != movement->x && movement->x != 0;
        modified_movement.x += move_sign.x)
    {
        col_grid_pos1.x = (col->transform.x + modified_movement.x) / tile_map->tile_set->tile_width;
        col_grid_pos2.x = (col->transform.x + modified_movement.x + col->w) / tile_map->tile_set->tile_width;
        col_grid_pos1.y = (col->transform.y + modified_movement.y) / tile_map->tile_set->tile_height;
        col_grid_pos2.y = (col->transform.y + modified_movement.y + col->h) / tile_map->tile_set->tile_height;

        if(move_sign.x < 0
            && (tile_map->collision_map[col_grid_pos1.y * tile_map->map_width + col_grid_pos1.x] != 0
            || tile_map->collision_map[col_grid_pos2.y * tile_map->map_width + col_grid_pos1.x] != 0))
        {
            modified_movement.x -= move_sign.x;
            break;
        }
        else if(move_sign.x > 0
            && (tile_map->collision_map[col_grid_pos1.y * tile_map->map_width + col_grid_pos2.x] != 0
            || tile_map->collision_map[col_grid_pos2.y * tile_map->map_width + col_grid_pos2.x] != 0))
        {
            modified_movement.x -= move_sign.x;
            break;
        }

        return modified_movement;
    }
}   