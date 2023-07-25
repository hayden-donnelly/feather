#include "animation.h"
#include "../../engine.h"
#include "../../component.h"
#include <stdio.h>

void update_anim(Component_Type *cmp_type)
{
    // animation speedup glitch is caused by timer accumulator in engine.c
    // - this has been fixed by moving anim update into the render loop but I might want to look further into it
    for(int i = 0; i < cmp_type->real_length; i++)
    {
        Anim_Controller *target = cmp_type->data[i];
        target->anims[target->anim_id].dt_accumulator += read_timer_dt();
        if(target->anims[target->anim_id].dt_accumulator >= target->anims[target->anim_id].speed)
        {
            target->frame_id++;
            target->anims[target->anim_id].dt_accumulator = 0;
        }
        if(target->frame_id >= target->anims[target->anim_id].frame_count)
        {
            if(!target->anims[target->anim_id].loop)
            {
                target->anim_id = target->default_anim_id;
            }
            target->frame_id = 0;//target->anims[target->anim_id].tile_ids[0];
        }
    }
}

void render_anim(Component_Type *cmp_type, Component_Type *pos)
{
    for(int i = 0; i < cmp_type->real_length; i++)
    {
        Anim_Controller *target = cmp_type->data[i];
        Position *target_pos = get_component(pos, target->entity_id);
        int x = 0;
        int y = 0;
        if(target_pos)
        {
            x = target_pos->x;
            y = target_pos->y;
        }
        // TODO: hacky solution
        int *tile_ids = malloc(sizeof(int));
        tile_ids[0] = target->anims[target->anim_id].tile_ids[target->frame_id];
        render_sprite(target->sprite, tile_ids, 1, 1, x, y);
        free(tile_ids);
    }
}

