#pragma once
#include "engine.h"

typedef struct Tile_Set
{
    unsigned int tile_width, tile_height;
    unsigned int number_of_tiles_horizontal, number_of_tiles_vertical;
    SDL_Texture *tex;
    SDL_Rect src;
    SDL_Rect dst;
} Tile_Set;

typedef struct Tile_Map
{
    Tile_Set *tile_set;
    int map_width, map_height;
    int collision_map[];
} Tile_Map;