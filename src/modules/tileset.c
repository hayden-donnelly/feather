#include "tileset.h"
#include "math.h"

Vec2_Int tile_coords_from_gid(int gid, Tileset *tileset)
{   
    Vec2_Int coords;
    coords.x = (int)(gid % tileset->number_of_tiles_horizontal) * tileset->tile_width;
    coords.y = (int)floor(gid / tileset->number_of_tiles_horizontal) * tileset->tile_width;
    return coords;
}