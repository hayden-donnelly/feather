#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <string.h>
#include "components.h"
#include "input.h"
#include "game.h"

// Timing
double timer_last;
double timer_now;
double timer_dt;
double timer_fixed_dt;
double timer_accumulator;

SDL_Window *window;
SDL_Renderer *renderer;

int engine_init(void);
void engine_cleanup(void);
void loop(void);

int cam_x;
int cam_y;

int running;

typedef struct Vec2_Int
{
    int x;
    int y;
} Vec2_Int;

typedef struct Player
{
    Transform transform;
    Sprite sprite;
    Box_Collider box_collider;
} Player;