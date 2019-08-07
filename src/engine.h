#pragma once
#include <SDL2/SDL.h>
#include "input.h"
#include "game.h"

SDL_Window *window;
SDL_Renderer *renderer;

int engine_init(void);
void engine_cleanup(void);
void loop(void);

int cam_x;
int cam_y;

int running;