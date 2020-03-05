#include <stdlib.h>
#include "grid_collider.h"

int grid_collision(Component_Type *grid_collider, Component_Type *position, 
                    Box_Collider *box_collider, int move_x, int move_y)
{
    for(int i = 0; i < grid_collider->real_length; i++)
    {
        Grid_Collider *target = grid_collider->data[i];
        Position *position = get_component(&position, target->entity_id);
        int move_sign_x = (int)copysign(1, move_x);
        int move_sign_y = (int)copysign(1, move_y);

        int col_grid_pos_left;
        int col_grid_pos_top;
        int col_grid_pos_right;
        int col_grid_pos_bottom;
        int iterative_move_x;
        int iterative_move_y;
        int collision_done;

        while(!collision_done)
        {
            if(abs(iterative_move_x) < abs(move_x))
            {
                iterative_move_x += move_sign_x;
                col_grid_pos_left = (position->x + box_collider->x + iterative_move_x) / target->cell_width;
                col_grid_pos_right = (position->x + box_collider->x + box_collider->w + iterative_move_x) / target->cell_width;
                col_grid_pos_top = (position->y + box_collider->y + iterative_move_y) / target->cell_height;
                col_grid_pos_bottom = (position->y + box_collider->y + + box_collider->h + iterative_move_y) / target->cell_height;
                

            }

            if(abs(iterative_move_y) < abs(move_y))
            {
                iterative_move_y += move_sign_y;
                col_grid_pos_left = (position->x + box_collider->x + iterative_move_x) / target->cell_width;
                col_grid_pos_right = (position->x + box_collider->x + box_collider->w + iterative_move_x) / target->cell_width;
                col_grid_pos_top = (position->y + box_collider->y + iterative_move_y) / target->cell_height;
                col_grid_pos_bottom = (position->y + box_collider->y + + box_collider->h + iterative_move_y) / target->cell_height;
            }
        }
    }
    return 0;
}

// Doesn't work do not uncomment
/*Vec2_Int move_sign;
    move_sign.x = (int)copysign(1, movement->x);
    move_sign.y = (int)copysign(1, movement->y);

    Vec2_Int col_grid_pos1;     // top left corner
    Vec2_Int col_grid_pos2;     // bottom right corner
    Vec2_Int modified_movement;

    // y collision
    for(modified_movement.y = 0; modified_movement.y != movement->y && movement->y != 0; 
        modified_movement.y += move_sign.y)
    {
        col_grid_pos1.x = (col->transform.pos.x + modified_movement.x) / tilemap->tileset->tile_width;
        col_grid_pos2.x = (col->transform.pos.x + modified_movement.x + col->w) / tilemap->tileset->tile_width;
        col_grid_pos1.y = (col->transform.pos.y + modified_movement.y) / tilemap->tileset->tile_height;
        col_grid_pos2.y = (col->transform.pos.y + modified_movement.y + col->h) / tilemap->tileset->tile_height;
    
        if(move_sign.y < 0
            && (tilemap->collision_map[col_grid_pos1.y * tilemap->map_width + col_grid_pos1.x] != 0
            || tilemap->collision_map[col_grid_pos1.y * tilemap->map_width + col_grid_pos2.x] != 0))
        {
            modified_movement.y -= move_sign.y;
            break;
        }
        else if(move_sign.y > 0
            && (tilemap->collision_map[col_grid_pos2.y * tilemap->map_width + col_grid_pos1.x] != 0
            || tilemap->collision_map[col_grid_pos2.y * tilemap->map_width + col_grid_pos2.x] != 0))
        {
            modified_movement.y -= move_sign.y;
            break;
        }
    }

    // x collision
    for(modified_movement.x = 0; modified_movement.x != movement->x && movement->x != 0;
        modified_movement.x += move_sign.x)
    {
        col_grid_pos1.x = (col->transform.pos.x + modified_movement.x) / tilemap->tileset->tile_width;
        col_grid_pos2.x = (col->transform.pos.x + modified_movement.x + col->w) / tilemap->tileset->tile_width;
        col_grid_pos1.y = (col->transform.pos.y + modified_movement.y) / tilemap->tileset->tile_height;
        col_grid_pos2.y = (col->transform.pos.y + modified_movement.y + col->h) / tilemap->tileset->tile_height;

        if(move_sign.x < 0
            && (tilemap->collision_map[col_grid_pos1.y * tilemap->map_width + col_grid_pos1.x] != 0
            || tilemap->collision_map[col_grid_pos2.y * tilemap->map_width + col_grid_pos1.x] != 0))
        {
            modified_movement.x -= move_sign.x;
            break;
        }
        else if(move_sign.x > 0
            && (tilemap->collision_map[col_grid_pos1.y * tilemap->map_width + col_grid_pos2.x] != 0
            || tilemap->collision_map[col_grid_pos2.y * tilemap->map_width + col_grid_pos2.x] != 0))
        {
            modified_movement.x -= move_sign.x;
            break;
        }
    }

    return modified_movement;
}*/