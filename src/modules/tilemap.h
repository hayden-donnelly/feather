#pragma once
#include "tileset.h"
#include "camera.h"
#include "box_collider.h"

typedef struct Tilemap
{
    Tileset *tileset;
    int map_width, map_height;
    int *gid_map;  // Stores the actual tile IDs for rendering
    int *collision_map;
} Tilemap;
Vec2_Int tilemap_collision(const Vec2_Int *movement, const Box_Collider *col, const Tilemap *tilemap);
void tilemap_render(const Tilemap *tilemap, const Camera *cam);