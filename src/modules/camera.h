#pragma once
#include <SDL2/SDL.h>
#include "utils.h"

typedef struct Camera
{
    Vec2_Int pos;
    SDL_Renderer *renderer;
} Camera;
Camera camera_init(Vec2_Int pos, SDL_Renderer *renderer);