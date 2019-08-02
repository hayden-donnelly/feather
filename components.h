#pragma once
#include "engine.h"

#define MAX_SPRITES 500
#define MAX_BOX_COLLIDERS 500

typedef struct Transform Transform;
struct Transform
{
    Transform *parent;
    // Offset from origin/parent
    int x, y;
};
Transform set_transform(int x, int y, Transform *parent);

typedef struct Sprite
{
    int active;
    Transform transform;
    SDL_Texture *tex;
    SDL_Rect dst;
} Sprite;
Sprite init_sprite(char *tex_path, Transform sprite_transform);
void subscribe_to_sprites(Sprite *desired_sprite);

typedef struct Box_Collider
{
    int active;
    Transform transform;
    int w, h;
} Box_Collider;
Box_Collider init_box_collider(int w, int h, Transform col_transform);
void subscribe_to_box_colliders(Box_Collider *desired_box_collider);

Sprite *sprites[MAX_SPRITES];
Box_Collider *box_colliders[MAX_BOX_COLLIDERS];