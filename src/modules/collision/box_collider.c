#include "box_collider.h"

Collision_Info box_collision(Component_Type *colliders, Component_Type *position, Box_Collider *active_collider, 
                            int move_x, int move_y, unsigned int collision_ids_length)
{
    int move_sign_x = (int)copysign(1, move_x);
    int move_sign_y = (int)copysign(1, move_y);

    Collision_Info collision_info;

    for(int i = 0; i < colliders->real_length; i++)
    {
        Box_Collider *target = colliders->data[i];
        Position *target_pos = get_component(position, target->entity_id);

        int iterative_move_x;
        int iterative_move_y;

        int collision_y_done;
        int collision_x_done;
        
        while(!collision_x_done && !collision_y_done)
        {
            if(abs(iterative_move_x) < abs(move_x) && !collision_x_done)
            {
                iterative_move_x += move_sign_x;
                if(active_collider->x + iterative_move_x < target->x + target->w &&
                    active_collider->x + iterative_move_x + active_collider->w > target->x &&
                    active_collider->y + iterative_move_y < target->y + target->h &&
                    active_collider->x + iterative_move_y + active_collider->h + target->y)
                {
                    if(!target->is_trigger)
                    {
                        iterative_move_x -= move_sign_x;
                        move_x = iterative_move_x;
                        collision_x_done = 1;
                    }
                    // TODO: add support for triggers
                }
            }

            if(abs(iterative_move_y) < abs(move_y) && !collision_y_done)
            {
                iterative_move_y += move_sign_y;
                if(active_collider->x + iterative_move_x < target->x + target->w &&
                    active_collider->x + iterative_move_x + active_collider->w > target->x &&
                    active_collider->y + iterative_move_y < target->y + target->h &&
                    active_collider->x + iterative_move_y + active_collider->h + target->y)
                {
                    if(!target->is_trigger)
                    {
                        iterative_move_y -= move_sign_y;
                        move_y = iterative_move_y;
                        collision_y_done = 1;
                    }
                    // TODO: add support for triggers
                }
            }
        }
    }

    collision_info.modified_move_x = move_x;
    collision_info.modified_move_y = move_y;
    return collision_info;
}