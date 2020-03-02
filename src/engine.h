#pragma once
#include <SDL2/SDL.h>
#include "input.h"

SDL_Window *window;
SDL_Renderer *renderer;

double read_timer_dt(void);

int engine_init(void);
void engine_cleanup(void);
void loop(void);

int running;