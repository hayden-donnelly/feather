#include "sprite.h"
#include "../../engine.h"

void render_sprite(Sprite *sprite, int *tile_ids, unsigned int id_array_width, 
                    unsigned int id_array_height, int pos_x, int pos_y)
{
    for(int x = 0; x < id_array_width; x++)
    {
        for(int y = 0; y < id_array_height; y++)
        {   
            int id = tile_ids[(y * id_array_width) + x];
            sprite->src.x = (int)(id % sprite->number_of_tiles_horizontal) * sprite->tile_width;
            sprite->src.y = (int)floor(id / sprite->number_of_tiles_horizontal) * sprite->tile_height;
            sprite->dst.x = x * sprite->tile_width + pos_x;
            sprite->dst.y = y * sprite->tile_height + pos_y;
            SDL_RenderCopy(renderer, sprite->tex, &sprite->src, &sprite->dst);
        }
    }
}