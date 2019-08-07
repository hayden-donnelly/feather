#pragma once
#include <SDL2/SDL.h>
#include "utils.h"

typedef struct Tileset
{
    unsigned int tile_width, tile_height;
    unsigned int number_of_tiles_horizontal, number_of_tiles_vertical;
    SDL_Texture *tex;
    SDL_Rect src;
    SDL_Rect dst;
} Tileset;
Vec2_Int tile_coords_from_gid(int gid, Tileset *tileset);