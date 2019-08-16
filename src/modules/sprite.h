#pragma once
#include <SDL2/SDL.h>
#include "transform.h"
#include "camera.h"

#define MAX_SPRITES 500

typedef struct Sprite
{
    int active;
    Transform transform;
    SDL_Texture *tex;
    SDL_Rect dst;
} Sprite;
Sprite sprite_init(char *tex_path, Transform sprite_transform, const Camera *cam);
void sprite_add(Sprite *sprite);
void sprite_remove(Sprite *sprite);
void sprite_render(const Camera *cam);

const int number_of_sprites;
Sprite *sprites;