#include <SDL2/SDL.h>
#include "tilemap.h"
#include "utils.h"

// Checks collision on the desired movement and returns
// modified movement if necessary to avoid clipping.
Vec2_Int tilemap_collision(const Vec2_Int *movement, const Box_Collider *col, const Tilemap *tilemap)
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
}

void tilemap_render(const Tilemap *tilemap, const Camera *cam)
{
    for(int x = 0; x < tilemap->map_width; x++)
    {
        for(int y = 0; y < tilemap->map_height; y++)
        {
            Vec2_Int tile = tile_coords_from_gid(tilemap->gid_map[(y * tilemap->map_width) + x], tilemap->tileset);
            tilemap->tileset->src.x = tile.x;
            tilemap->tileset->src.y = tile.y;
            tilemap->tileset->dst.x = x * tilemap->tileset->tile_width + cam->pos.x;
            tilemap->tileset->dst.y = y * tilemap->tileset->tile_height + cam->pos.y;
            SDL_RenderCopy(cam->renderer, tilemap->tileset->tex, &tilemap->tileset->src, &tilemap->tileset->dst);
        }
    }
}