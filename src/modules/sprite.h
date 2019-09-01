#pragma once
#include <SDL2/SDL.h>
#include "transform.h"
#include "camera.h"

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
void sprite_module_init(const int max_sprites);
void sprite_cleanup_module(void);