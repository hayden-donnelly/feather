#pragma once
#include <SDL2/SDL.h>

typedef struct
{
    unsigned int tile_width, tile_height;
    unsigned int number_of_tiles_horizontal, number_of_tiles_vertical;
    SDL_Texture *tex;
    SDL_Rect src;
    SDL_Rect dst;
} Sprite;

void render_sprite(Sprite *sprite, int *tile_ids ,unsigned int id_array_width, unsigned int id_array_height);