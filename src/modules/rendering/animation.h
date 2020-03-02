#pragma once
#include "sprite.h"
#include "../../component.h"

typedef struct
{
    unsigned int frame_count;
    unsigned int *tile_ids;   // ID's corresponding to tileset
    char loop;
} Anim;

typedef struct
{
    int entity_id;
    Sprite *sprite;
    Anim *anims;
    unsigned int anim_id;
    unsigned int frame_id;
    unsigned int default_anim_id;
} Anim_Controller;

void update_anim(Component_Type *cmp_type);
void render_anim(Component_Type *component);