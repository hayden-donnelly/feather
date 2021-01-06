#include "tilemap.h"

void render_tilemap(Component_Type *cmp_type, Component_Type *pos)
{
    for(int i = 0 ; i < cmp_type->real_length; i++)
    {
        Tilemap *target = cmp_type->data[i];
        //Position *target_pos = get_component(pos, target->entity_id);
        // Temporary hack
        Position *target_pos = get_component(pos, 32); // Hardcoded player pos id
        int x = 0;
        int y = 0;
        if(target_pos)
        {
            x = target_pos->x;
            y = target_pos->y;
        }
        render_sprite(target->sprite, target->sprite_ids, target->map_width, 
                        target->map_height, x, y);
    }
}