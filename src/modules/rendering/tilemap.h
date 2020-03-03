#pragma once
#include "../../component.h"
#include "sprite.h"

typedef struct
{
    int entity_id;
    unsigned int map_width;
    unsigned int map_height;
    int *sprite_ids;
    Sprite *sprite;
} Tilemap;

void render_tilemap(Component_Type *cmp_type, Component_Type *pos);