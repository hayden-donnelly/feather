#include "engine.h"

Transform set_transform(int x, int y, Transform *parent)
{
    Transform new_transform;
    new_transform.parent = parent;
    new_transform.x = x;
    new_transform.y = y;
    return new_transform;
}

Sprite init_sprite(char *tex_path, Transform sprite_transform)
{
    Sprite new_sprite;
    new_sprite.active = 1;
    new_sprite.transform = sprite_transform;
    new_sprite.tex = IMG_LoadTexture(renderer, tex_path);
    int w, h;
    SDL_QueryTexture(new_sprite.tex, NULL, NULL, &w, &h);
    new_sprite.dst.w = w;
    new_sprite.dst.h = h;
    new_sprite.dst.x = 0;
    new_sprite.dst.y = 0;
    return new_sprite;
}

void subscribe_to_sprites(Sprite *desired_sprite)
{
    for(int i = 0; i < MAX_SPRITES; i++)
    {
        if(sprites[i] == NULL || sprites[i]->active == 0)
        {
            sprites[i] = desired_sprite;
            return;
        }
    }
}

Box_Collider init_box_collider(int w, int h, Transform col_transform)
{
    Box_Collider new_box_collider;
    new_box_collider.active = 1;
    new_box_collider.transform = col_transform;
    new_box_collider.w = w;
    new_box_collider.h = h;
    return new_box_collider;
}

void subscribe_to_box_colliders(Box_Collider *desired_box_collider)
{
    for(int i = 0; i < MAX_BOX_COLLIDERS; i++)
    {
        if(box_colliders[i] == NULL || box_colliders[i]->active == 0)
        {
            box_colliders[i] = desired_box_collider;
            return;
        }
    }
}