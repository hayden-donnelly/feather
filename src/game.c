#include <stdio.h>
#include "engine.h"
#include "component.h"
#include "modules/collision/grid_collider.h"
#include <SDL2/SDL_image.h>

#define MAX_ENTITIES 500

// This file is used for testing many different parts of the engine so it's very messy right now

Box_Collider *bc;


int map1[] = {   2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 
                21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23,  2,  2, 21, 22, 22, 22, 22, 22, 23, 2,  21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 
                24,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 15,  2,  2, 17,  1,  1,  1,  1,  1, 15,  2, 17,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1, 26, 
                24,  1,  3,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  3,  1,  1,  1, 15,  2,  2, 17,  1,  1,  1,  1,  1, 15,  2, 17,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 26, 
                24,  1,  1,  1,  1,  1, 12, 13, 13, 13, 13, 13, 14,  1,  1,  1,  1,  1, 15,  2,  2, 17,  1,  1,  1,  1,  1, 15,  2, 17,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1, 26, 
                24,  1,  1,  1, 12, 28, 29,  2,  2,  2,  2,  2, 17,  3,  1,  1,  3,  1, 15,  2,  2, 27, 13, 13, 14,  1,  1, 15,  2, 17,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 26, 
                24,  1,  1,  3, 15,  2,  2,  2,  2,  2,  2,  2, 17,  1,  1,  1,  1,  1, 15,  2,  2,  2,  2,  2, 17,  1,  1, 15,  2, 17,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1, 26, 
                24,  3,  1,  1, 15,  2,  2,  2,  2,  2,  2,  2, 27, 13, 14,  1,  1,  1, 18, 19, 19, 19, 23,  2, 27, 13, 13, 29,  2, 17,  1,  1,  1,  1,  1, 30, 31, 31, 31, 32,  1, 30, 31, 31, 31, 32,  1,  1,  1, 26, 
                24,  1,  1,  1, 15,  2,  2,  2,  2,  2,  2,  2,  2,  2, 17,  1,  1,  1,  1,  1,  1,  1, 15,  2,  2,  2,  2,  2,  2, 17,  1,  3,  1,  1,  1, 33, 34, 34, 34, 35,  1, 33, 34, 34, 34, 35,  1,  1,  1, 26, 
                24,  1,  3,  1, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20,  1,  1,  1,  3,  1,  1,  1, 15,  2, 21, 19, 19, 19, 19, 20,  1,  1,  1,  1,  1, 33, 34, 34, 34, 35,  1, 33, 34, 34, 34, 35,  1,  1,  1, 26, 
                24,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1, 15,  2, 17,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 36, 37, 37, 37, 38,  1, 36, 37, 37, 37, 38,  1,  1,  1, 26, 
                24,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 15,  2, 17,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 26, 
                24,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1, 18, 19, 20,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1, 30, 31, 31, 31, 32,  1, 30, 31, 31, 31, 32,  1,  1,  1, 26, 
                24,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1, 33, 34, 34, 34, 35,  1, 33, 34, 34, 34, 35,  1,  1,  1, 26, 
                24,  3,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 33, 34, 34, 34, 35,  1, 33, 34, 34, 34, 35,  1,  1,  1, 26, 
                24,  1,  1,  1,  1, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14,  1,  1,  1,  1,  1, 12, 13, 14,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1, 36, 37, 37, 37, 38,  1, 36, 37, 37, 37, 38,  1,  1,  1, 26, 
                24,  1,  1,  1,  3, 15,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 17,  1,  1,  1,  3,  1, 15,  2, 17,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1, 26, 
                24,  1,  3,  1,  1, 15,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 27, 13, 14,  1,  1,  1, 15,  2, 17,  1,  3,  1,  1,  1,  3,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1, 26, 
                24,  1,  1,  1,  1, 15,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 17,  3,  1,  3, 15,  2, 17,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 26, 
                27, 13, 13, 13, 13, 29,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 27, 13, 13, 13, 29,  2, 27, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 29, 
                 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 
            };

 int map2[] = {  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 
                21, 22, 22, 22, 22, 22, 22, 23,  2, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 
                24,  1,  1,  1,  1,  1,  1, 15,  2, 17,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1, 26, 
                24,  1,  1,  1,  3,  1,  1, 15,  2, 17,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1, 26, 
                24,  1,  3,  1,  1,  1,  1, 15,  2, 17,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  3,  1,  1,  3,  1, 12, 13, 13, 13, 13, 29, 
                24,  1,  1,  1,  1,  1,  1, 15,  2, 27, 13, 14,  1,  1,  3,  1,  1,  3,  1,  1,  1,  1,  1,  1, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32,  1,  1,  1,  1,  1,  1,  1,  1,  1, 15,  2,  2,  2,  2,  2, 
                24,  1,  1,  1,  1,  1,  1, 15,  2,  2,  2, 17,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35,  1,  1,  1,  1,  1,  1,  1,  1,  1, 15,  2,  2,  2,  2,  2, 
                24,  1,  1,  1,  3,  1,  1, 18, 19, 23,  2, 17,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  3,  1, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35,  1,  1,  1,  1,  1,  1,  3,  1,  1, 15,  2,  2,  2,  2,  2, 
                24,  1,  1,  1,  1,  1,  1,  1,  1, 15,  2, 27, 13, 13, 13, 13, 14,  1,  1,  1,  3,  1,  1,  1, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35,  1,  1,  3,  1,  1,  1,  1,  1,  1, 15,  2,  2,  2,  2,  2, 
                24,  1,  1,  3,  1,  1,  1,  1,  1, 15,  2,  2,  2,  2,  2,  2, 17,  1,  1,  1,  1,  1,  1,  1, 36, 37, 37, 37, 37, 37, 37, 37, 37, 37, 38,  1,  1,  1, 12, 13, 13, 13, 13, 13, 29,  2,  2,  2,  2,  2, 
                24,  3,  1,  1,  1,  1,  1,  1,  1, 18, 19, 19, 19, 19, 19, 19, 20,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 15,  2,  2,  2,  2,  2, 2,  2,  2,  2,  2,  2, 
                24,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 32,  1,  1,  1, 15,  2, 21, 19, 19, 19, 23,  2,  2,  2,  2,  2, 
                27, 13, 13, 13, 13, 13, 14,  1,  1,  3,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35,  3,  1,  1, 15,  2, 17,  1,  3,  1, 15,  2,  2,  2,  2,  2, 
                 2,  2,  2,  2,  2,  2, 17,  1,  1,  1, 12, 13, 13, 13, 14,  1,  1,  1,  3,  1,  1,  1,  1,  1, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35,  1,  1,  1, 15,  2, 17,  1,  1,  1, 18, 19, 19, 19, 19, 23, 
                21, 19, 19, 19, 19, 19, 20,  1,  3,  1, 15,  2,  2,  2, 17,  1,  3,  1,  1,  1,  1,  1,  1,  1, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35,  1,  1,  1, 15,  2, 17,  1,  1,  1,  3,  1,  1,  1,  1, 26, 
                24,  3,  1,  1,  1,  1,  1,  1,  1,  1, 15,  2,  2,  2, 17,  1,  1,  1,  1,  1,  1,  3,  1,  1, 36, 37, 37, 37, 37, 37, 37, 37, 37, 37, 38,  1,  1,  1, 15,  2, 17,  1,  3,  1,  1,  1,  3,  1,  1, 26, 
                24,  1,  1,  3,  1,  1,  3,  1,  1,  1, 15,  2,  2,  2, 17,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1, 15,  2, 17,  1,  1,  1,  1,  1,  1,  1,  1, 26, 
                24,  1,  1,  1,  1,  1,  1,  1,  1,  1, 15,  2,  2,  2, 17,  1,  1,  3,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1, 15,  2, 17,  1,  1,  1,  3,  1,  1,  1,  1, 26, 
                24,  1,  3,  1,  1,  3,  1,  1,  1,  1, 15,  2,  2,  2, 17,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1, 15,  2, 17,  1,  3,  1,  1,  1,  1,  3,  1, 26, 
                27, 13, 13, 13, 13, 13, 13, 13, 13, 13, 29,  2,  2,  2, 27, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 29,  2, 27, 13, 13, 13, 13, 13, 13, 13, 13, 29, 
                 2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2, 
            };

int map3[] = { 39, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 41, 34, 34, 34, 39, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 41, 34, 34, 34, 34, 34, 34, 34, 34, 
               35,  1,  1,  1,  1,  3,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1, 33, 34, 34, 34, 35,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 33, 34, 34, 34, 34, 34, 34, 34, 34, 
               35,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 33, 34, 34, 34, 35,  1,  1,  1,  1,  3,  1,  1,  1,  3,  1,  1, 33, 34, 34, 34, 34, 34, 34, 34, 34,
               35,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1, 33, 34, 34, 34, 35,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1, 33, 34, 34, 34, 34, 34, 34, 34, 34,
               45, 46, 46, 46, 46, 46, 46, 46, 32,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  3,  1,  3,  1,  1, 33, 34, 34, 34, 35,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 33, 34, 34, 34, 34, 34, 34, 34, 34,
               34, 34, 34, 34, 34, 34, 34, 34, 35,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 33, 34, 34, 34, 35,  1,  1,  1,  1,  1,  1,  3,  1,  1,  3,  1, 33, 34, 34, 34, 34, 34, 34, 34, 34,
               34, 34, 34, 34, 34, 34, 34, 34, 35,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3, 33, 34, 34, 34, 35,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1, 33, 34, 34, 34, 34, 34, 34, 34, 34,
               34, 34, 34, 34, 34, 34, 34, 34, 45, 46, 46, 46, 46, 32,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1, 33, 34, 34, 34, 35,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1, 33, 34, 34, 34, 34, 34, 34, 34, 34,
               34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35,  3,  1,  1,  1,  1,  3, 30, 46, 46, 46, 46, 47, 34, 34, 34, 45, 46, 46, 46, 32,  1,  1,  1,  1,  1,  1,  1, 36, 37, 37, 37, 37, 37, 37, 37, 41,
               39, 37, 37, 37, 37, 37, 37, 37, 37, 41, 34, 34, 34, 35,  1,  1,  1,  1,  1,  1, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1, 33,
               35,  1,  1,  1,  1,  3,  1,  1,  1, 33, 34, 34, 34, 35,  1,  3,  1,  1,  1,  1, 36, 37, 37, 37, 37, 37, 37, 37, 37, 37, 41, 34, 34, 35,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1, 33,
               35,  1,  3,  1,  1,  1,  1,  3,  1, 36, 37, 37, 37, 38,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1, 33, 34, 34, 45, 46, 46, 46, 32,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 33,
               35,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3, 33, 34, 34, 34, 34, 34, 34, 35,  3,  1,  3,  1,  1,  1,  1,  1,  1,  3,  1, 33,
               35,  1,  1,  1,  3,  1,  1,  1,  1,  3,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  3,  1,  1,  1, 33, 34, 34, 34, 34, 34, 34, 35,  1,  1,  1,  1,  1,  3,  1,  1,  1,  1,  1, 33,
               35,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1, 33, 34, 34, 34, 34, 34, 34, 35,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 33,
               45, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 46, 32,  1,  1,  1,  1,  1,  1,  1,  1,  1, 36, 37, 37, 37, 37, 37, 37, 38,  1,  3,  1,  1,  1,  1,  1,  1,  1,  1,  1, 33,
               34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  3,  1,  1,  1, 33,
               34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 45, 46, 46, 32,  1,  3,  1,  1,  3,  1, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 47,
               34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35,  1,  1,  1,  1,  1,  1, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
               34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 35,  1,  1,  1,  3,  1,  1, 33, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
               34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 45, 46, 46, 46, 46, 46, 46, 47, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 34, 
            };

void game_init(void)
{
    components = malloc(sizeof(Components));
    components->health = init_component_type(MAX_ENTITIES);
    components->position = init_component_type(MAX_ENTITIES);
    components->anim_controller = init_component_type(MAX_ENTITIES);
    components->tilemap = init_component_type(1);
    components->grid_collider = init_component_type(1);

    // Player box collider - need to add to component array
    bc = malloc(sizeof(Box_Collider));
    bc->entity_id = 500;
    bc->w = 16;
    bc->h = 16;

    // Random components
    Health *health = malloc(sizeof(Health));
    health->enitity_id = 30;
    health->hp = 20;
    Health *health4 = malloc(sizeof(Health));
    health4->enitity_id = 31;
    health4->hp = 5;

    add_component(&components->health, health, health->enitity_id);
    add_component(&components->health, health4, health4->enitity_id);

    Health *health2 = get_component(&components->health, 30);
    health2->hp -= 10;
    printf("HP: %d\n", health2->hp);

    Health *health3 = get_component(&components->health, 30);
    printf("HP: %d\n", health3->hp);

    remove_component(&components->health, 30);
    if(get_component(&components->health, 30) == NULL)
    {
        printf("it works\n");
    }

    Health *health5 = get_component(&components->health, 31);
    printf("HP2: %d\n", health5->hp);
    health3 = get_component(&components->health, 30);
    if(health3 != NULL) { printf("HP: %d\n", health3->hp); }

    Position *pos1 = malloc(sizeof(Position));
    pos1->entity_id = 30;
    pos1->x = 120;
    pos1->y = 50;
    add_component(&components->position, pos1, 30);

    Position *pos2 = malloc(sizeof(Position));
    pos2->entity_id = 32;
    pos2->x = 0;
    pos2->y = 0;
    add_component(&components->position, pos2, 32);

    // Animation
    Anim_Controller *anim_controller1 = malloc(sizeof(Anim_Controller));
    anim_controller1->entity_id = 30;
    anim_controller1->sprite = malloc(sizeof(Sprite));
    anim_controller1->sprite->tile_width = 16;
    anim_controller1->sprite->tile_height = 16;
    anim_controller1->sprite->number_of_tiles_horizontal = 16;
    anim_controller1->sprite->number_of_tiles_vertical = 7;
    anim_controller1->sprite->tex = IMG_LoadTexture(renderer, "assets/16x16_test.png");
    SDL_Rect draw_rect;
    draw_rect.x = 0;
    draw_rect.y = 0;
    draw_rect.w = 16;
    draw_rect.h = 16;
    anim_controller1->sprite->src = draw_rect;
    anim_controller1->sprite->dst = draw_rect;
    anim_controller1->anims = malloc(sizeof(Anim)*3);
    anim_controller1->anim_id = 0;
    anim_controller1->frame_id = 0;
    anim_controller1->default_anim_id = 0;

    Anim anim1;  
    anim1.frame_count = 2;
    anim1.tile_ids = malloc(sizeof(int)*2);
    // Character 1
    anim1.tile_ids[0] = 1;
    anim1.tile_ids[1] = 2;
    // Character 2
    //anim1.tile_ids[0] = 5;
    //anim1.tile_ids[1] = 6;
    // Character 3
    //anim1.tile_ids[0] = 14;
    //anim1.tile_ids[1] = 13;

    anim1.loop = 1;
    anim1.speed = 0.5f;
    anim_controller1->anims[0] = anim1;

    add_component(&components->anim_controller, anim_controller1, 30);

    // Tilemap
    Tilemap *tilemap1 = malloc(sizeof(Tilemap));
    tilemap1->sprite_ids = (int*)&map1;
    tilemap1->map_width = 50;
    tilemap1->map_height = 21;
    tilemap1->entity_id = 500;
    tilemap1->sprite = malloc(sizeof(Sprite));
    tilemap1->sprite->number_of_tiles_horizontal = 3;
    tilemap1->sprite->number_of_tiles_vertical = 4;
    tilemap1->sprite->tile_width = 16;
    tilemap1->sprite->tile_height = 16;
    tilemap1->sprite->tex = IMG_LoadTexture(renderer, "assets/tiles2.png");
    tilemap1->sprite->dst = draw_rect;
    tilemap1->sprite->src = draw_rect;

    add_component(&components->tilemap, tilemap1, 500);

    // Grid Collider
    Grid_Collider *grid_col = malloc(sizeof(Grid_Collider));
    grid_col->entity_id = 500;
    grid_col->grid_width = 20;
    grid_col->grid_height = 20;
    grid_col->cell_width = 16;
    grid_col->cell_height = 16;
    grid_col->collision_ids = malloc(sizeof(int)*400);
    for(int i = 0; i < 400; i++)
    {
        /*if(i < 20)
        {
            grid_col->collision_ids[i] = 1;
        }
        else if(i > 380)
        {
            grid_col->collision_ids[i] = 1;
        }
        else
        {
            grid_col->collision_ids[i] = 0;
        }*/

        grid_col->collision_ids[i] = 0;
    }
    add_component(&components->grid_collider, grid_col, 500);

    // Grid Collider Position
    Position *grid_col_pos = malloc(sizeof(Position));
    grid_col_pos->entity_id = 500;
    grid_col_pos->x = 0;
    grid_col_pos->y = 0;
    add_component(&components->position, grid_col_pos, 500);

    // Input 
    number_of_game_inputs = 4;
    game_inputs = malloc(sizeof(Game_Input)*4);

    Game_Input left;
    left.scancode = SDL_SCANCODE_D;
    left.input_name = "left";
    game_inputs[0] = left;

    Game_Input right;
    right.scancode = SDL_SCANCODE_A;
    right.input_name = "right";
    game_inputs[1] = right;

    Game_Input up;
    up.scancode = SDL_SCANCODE_W;
    up.input_name = "up";
    game_inputs[2] = up;

    Game_Input down;
    down.scancode = SDL_SCANCODE_S;
    down.input_name = "down";
    game_inputs[3] = down;
}

void game_update(void)
{
    //update_anim(&components->anim_controller); - moved to render loop

    Position *player_pos = get_component(&components->position, 32);
    //bc->x = player_pos->x;
    //bc->y = player_pos->y;

    int move_x = 0;
    int move_y = 0;

    if(player_pos)
    {
        if(get_input("left"))
        {
            move_x += 1;
        }
        else if(get_input("right"))
        {
            move_x -= 1;
        }
        else if(get_input("up"))
        {
            move_y -= 1;
        }
        else if(get_input("down"))
        {
            move_y += 1;
        }
    }

    Collision_Info col_info = grid_collision(&components->grid_collider, &components->position, bc, move_x, move_y);
    player_pos->x += col_info.modified_move_x;
    player_pos->y += col_info.modified_move_y;
    player_pos->x -= move_x;
    player_pos->y -= move_y;
}

void game_cleanup(void)
{
    printf("Game Cleanup\n");
}

void game_render(void)
{
    update_anim(&components->anim_controller);
    render_tilemap(&components->tilemap, &components->position);
    render_anim(&components->anim_controller, &components->position);
}