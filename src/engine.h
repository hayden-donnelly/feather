#pragma once
#include <SDL2/SDL.h>
#include "input.h"

extern SDL_Window *window;
extern SDL_Renderer *renderer;

double read_timer_dt(void);

int engine_init(void);
void engine_cleanup(void);
void loop(void);

extern int running;