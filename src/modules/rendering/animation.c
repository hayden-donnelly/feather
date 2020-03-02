#include "animation.h"
#include "../../engine.h"
#include "../../component.h"
#include <stdio.h>

void update_anim(Component_Type *cmp_type)
{
    for(int i = 0; i < cmp_type->real_length; i++)
    {
        Anim_Controller *target = cmp_type->data[i];
        printf("%f\n", target->anims[target->anim_id].dt_accumulator);
        target->anims[target->anim_id].dt_accumulator += 100 * read_timer_dt();
        if(target->anims[target->anim_id].dt_accumulator >= target->anims[target->anim_id].speed)
        {
            target->frame_id++;
            target->anims[target->anim_id].dt_accumulator = 0;
        }
        if(target->frame_id > target->anims[target->anim_id].frame_count)
        {
            if(!target->anims[target->anim_id].loop)
            {
                target->frame_id = target->default_anim_id;
            }
            target->frame_id = 0;
        }
    }
}

void render_anim(Component_Type *cmp_type)
{
    for(int i = 0; i < cmp_type->real_length; i++)
    {
        Anim_Controller *target = cmp_type->data[i];
        // TODO: hacky solution
        int *tile_ids = malloc(sizeof(int));
        tile_ids[0] = target->frame_id;
        render_sprite(target->sprite, tile_ids, 1, 1);
        free(tile_ids);
    }
}

